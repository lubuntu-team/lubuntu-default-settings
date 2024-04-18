// Copyright (C) 2024 Simon Quigley <tsimonq2@ubuntu.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <QApplication>
#include <QSystemTrayIcon>
#include <QtDBus/QtDBus>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create and set application icon
    QIcon appIcon = QIcon::fromTheme("dialog-information");
    QApplication::setWindowIcon(appIcon);

    // DBus interface to systemd
    QDBusInterface systemd("org.freedesktop.systemd1",
                           "/org/freedesktop/systemd1",
                           "org.freedesktop.systemd1.Manager",
                           QDBusConnection::systemBus());

    // Retrieve current status of snapd.seeded.service, which tracks the preseed process
    QDBusMessage methodCall = systemd.call("GetUnit", "snapd.seeded.service");
    QDBusObjectPath unitPath = methodCall.arguments().at(0).value<QDBusObjectPath>();
    QDBusInterface unit("org.freedesktop.systemd1",
                        unitPath.path(),
                        "org.freedesktop.systemd1.Unit",
                        QDBusConnection::systemBus());
    QVariant activeState = unit.property("ActiveState");
    QVariant subState = unit.property("SubState");

    // System tray icon setup
    QSystemTrayIcon trayIcon(appIcon);
    trayIcon.setToolTip("Snap Installation Monitor");

    // Initial message displayed in the system tray
    auto showMessage = [&trayIcon]() {
        trayIcon.showMessage("Installation Notice", "Finalizing installation of snaps, please wait...",
                             QSystemTrayIcon::Information, 15000);
    };

    // If the user clicks the system tray icon, display the notification again
    QObject::connect(&trayIcon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            showMessage();
        }
    });

    // Exit immediately if the service is "active (exited)", launch the GUI parts otherwise
    if (activeState.toString() == "active" && subState.toString() == "exited") { return 0; }
    trayIcon.show();
    showMessage();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&unit, &trayIcon]() {
        QVariant newState = unit.property("ActiveState");
        QVariant newSubState = unit.property("SubState");
        if (newState.toString() == "active" && newSubState.toString() == "exited") {
            trayIcon.hide();
            QApplication::quit();
        }
    });

    timer.start(5000); // Check every 5 seconds

    return app.exec();
}
