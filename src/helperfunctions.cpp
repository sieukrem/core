#include "helperfunctions.h"
#include <QQmlContext>
#include <QRegExp>
#include <QHostInfo>
#include <QFile>
#include <QDir>

namespace QFlow{

HelperFunctions::HelperFunctions()
{
}
HelperFunctions::~HelperFunctions()
{
}

bool HelperFunctions::isError(ErrorInfo info)
{
    bool res = info;
    return res;
}
QString HelperFunctions::errorText(ErrorInfo info)
{
    return info.errorText();
}

QObject* helperfunctions_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    HelperFunctions* singleton = new HelperFunctions();
    return singleton;
}
Timespan HelperFunctions::timespan(QString value)
{
    Timespan ts = Timespan::fromString(value);
    return ts;
}
Rational HelperFunctions::rational(int p, int q)
{
    return Rational(p,q);
}
Rational HelperFunctions::rational(QString str)
{
    return Rational::fromString(str);
}
IntRange HelperFunctions::intRange(int low, int high)
{
    return IntRange(low, high);
}
QString HelperFunctions::localHostName()
{
    return QHostInfo::localHostName();
}
bool HelperFunctions::copy(const QString &fileName, const QString &newName)
{
    return QFile::copy(fileName, newName);
}
bool HelperFunctions::mkdir(const QString &dirName) const
{
    QDir dir;
    return dir.mkpath(dirName);
}
QString HelperFunctions::currentDir()
{
    return QDir::currentPath();
}

qreal Math::scale(qreal value, qreal fromMin, qreal fromMax, qreal toMin, qreal toMax)
{
    qreal insize = fromMax - fromMin;
    qreal outsize = toMax - toMin;
    qreal result = (((value - fromMin)/insize)*outsize)+toMin;
    return result;
}
qreal Math::scale(qreal value, RealRange from, RealRange to)
{
    return Math::scale(value, from.from(), from.to(), to.from(), to.to());
}
int toFourCC(const QString str)
{
    QString newStr = "    ";
    newStr.replace(0,str.length(), str);
    return ((((int)newStr[0].toLatin1()))+(((int)newStr[1].toLatin1())<<8)+(((int)newStr[2].toLatin1())<<16)+(((int)newStr[3].toLatin1())<<24));
}
QString getStringFromUnsignedChar( unsigned char *str ){
    QString result = "";
    size_t lengthOfString = strlen( reinterpret_cast<const char*>(str) );

    for( int i = 0; i < lengthOfString; i++ ){
        result.append(str[i]);
    }

    return result;
}
QString expand_environment_variables(QString s)
{
    QString r(s);
    QRegExp env_var("\\$([A-Za-z0-9_]+)");
    int i;

    while((i = env_var.indexIn(r)) != -1) {
        QByteArray value(qgetenv(env_var.cap(1).toLatin1().data()));
        if(value.size() > 0) {
            r.remove(i, env_var.matchedLength());
            r.insert(i, value);
        } else
            break;
    }
    return r;
}
Timespan HelperFunctions::newTimespan(QString value)
{
    return Timespan::fromString(value);
}
}
