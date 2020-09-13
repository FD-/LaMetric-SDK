/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QABSTRACTXMLRECEIVER_H
#define QABSTRACTXMLRECEIVER_H

#include <QtCore/QVariant>
#include <QtCore/QScopedPointer>
#include <QtXmlPatterns/QXmlNodeModelIndex>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(XmlPatterns)

class QAbstractXmlReceiverPrivate;
class QXmlName;

namespace QPatternist
{
    class Item;
}

class Q_XMLPATTERNS_EXPORT QAbstractXmlReceiver
{
public:
    QAbstractXmlReceiver();

    virtual ~QAbstractXmlReceiver();

    virtual void startElement(const QXmlName &name) = 0;
    virtual void endElement() = 0;
    virtual void attribute(const QXmlName &name,
                           const QStringRef &value) = 0;
    virtual void comment(const QString &value) = 0;
    virtual void characters(const QStringRef &value) = 0;
    virtual void startDocument() = 0;
    virtual void endDocument() = 0;

    virtual void processingInstruction(const QXmlName &target,
                                       const QString &value) = 0;

    virtual void atomicValue(const QVariant &value) = 0;
    virtual void namespaceBinding(const QXmlName &name) = 0;
    virtual void startOfSequence() = 0;
    virtual void endOfSequence() = 0;

    /* The members below are internal, not part of the public API, and
     * unsupported. Using them leads to undefined behavior. */
    virtual void whitespaceOnly(const QStringRef &value);
    virtual void item(const QPatternist::Item &item);

protected:
    QAbstractXmlReceiver(QAbstractXmlReceiverPrivate *d);
    QScopedPointer<QAbstractXmlReceiverPrivate> d_ptr;

    void sendAsNode(const QPatternist::Item &outputItem);
private:
    template<const QXmlNodeModelIndex::Axis axis>
    void sendFromAxis(const QXmlNodeModelIndex &node);
    Q_DISABLE_COPY(QAbstractXmlReceiver)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif
