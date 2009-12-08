#ifndef SIMPLESOAPPARSER_H
#define SIMPLESOAPPARSER_H

#include <QXmlDefaultHandler>


class SimpleSoapParser : public QXmlDefaultHandler
{
public:
    SimpleSoapParser();

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);
    QString errorString() const;

    QString method(){return this->m_method;}
    QString arg(int index){
        if (index < args.size()){
           return args.at(index);
        }
        return QString("");
    }

private:

    QString currentText;
    QString errorStr;
    bool metSoapTag;

    QString m_method;
    QStringList args;

};

#endif // SIMPLESOAPPARSER_H
