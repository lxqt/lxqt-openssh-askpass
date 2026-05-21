/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2012 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include <LXQt/Application>
#include <QCommandLineParser>

#include "mainwindow.h"

constexpr const char *PROMPT_TYPE_ENV_VAR = "SSH_ASKPASS_PROMPT";

int main(int argc, char *argv[])
{
    LXQt::Application a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("LXQt OpenSSH Askpass"));
    const QString VERINFO = QStringLiteral(LXQT_ASKPASS_VERSION
                                           "\nliblxqt   " LXQT_VERSION
                                           "\nQt        " QT_VERSION_STR);
    a.setApplicationVersion(VERINFO);
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(a);

    QString prompt = QObject::tr("unknown request");
    const QStringList arguments = parser.positionalArguments();
    if (arguments.count() == 1) {
        prompt = arguments.at(0);
    }

    PromptType promptType = PromptType::Entry;
    const QString promptTypeString = qEnvironmentVariable(PROMPT_TYPE_ENV_VAR);
    if (promptTypeString == QLatin1String("confirm")) {
        promptType = PromptType::Confirm;
    } else if (promptTypeString == QLatin1String("none")) {
        promptType = PromptType::None;
    }

    MainWindow w(prompt, promptType);
    w.show();

    return a.exec();
}
