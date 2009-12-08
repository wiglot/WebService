

/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "simplesoapparser.h"
#include <QDebug>

SimpleSoapParser::SimpleSoapParser()
{

    metSoapTag = false;
    m_method = "";
}

bool SimpleSoapParser::startElement(const QString & /* namespaceURI */,
                               const QString & /* localName */,
                               const QString &qName,
                               const QXmlAttributes &/*attributes*/)
{
    if (!metSoapTag && qName != "SOAP-ENV:Envelope") {
        errorStr = QObject::tr("The file is not an XBEL file.");
        return false;
    }

    if (qName == "SOAP-ENV:Envelope") {
        metSoapTag = true;
    } else if (qName == "ExistLogin") {
        m_method = qName;
    } else if (qName == "CreateUser") {
        m_method = qName;
    }
    currentText.clear();
    return true;
}

bool SimpleSoapParser::endElement(const QString & /* namespaceURI */,
                             const QString & /* localName */,
                             const QString &qName)
{
    if (qName == "login" || qName == "pass") {
        args.append(currentText);
    }
    return true;
}

bool SimpleSoapParser::characters(const QString &str)
{
    currentText += str;
    return true;
}

bool SimpleSoapParser::fatalError(const QXmlParseException &exception)
{
    qDebug() << QObject::tr("SAX Bookmarks"),
                             QObject::tr("Parse error at line %1, column %2:\n"
                                         "%3")
                             .arg(exception.lineNumber())
                             .arg(exception.columnNumber())
                             .arg(exception.message());
    return false;
}

QString SimpleSoapParser::errorString() const
{
    return errorStr;
}

