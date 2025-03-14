﻿/*
 *  Copyright (C) 2016 Enrico Mariotti <enricomariotti@yahoo.it>
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_CSVPARSER_H
#define KEEPASSX_CSVPARSER_H

#include <QBuffer>
#include <QTextStream>

class QIODevice;

typedef QStringList CsvRow;
typedef QList<CsvRow> CsvTable;

class CsvParser
{

public:
    CsvParser();
    ~CsvParser();
    // read data from device and parse it
    bool parse(QIODevice* device);
    bool isFileLoaded();
    // reparse the same buffer (device is not opened again)
    bool reparse();
    void setCodec(const QString& s);
    void setComment(const QChar& c);
    void setFieldSeparator(const QChar& c);
    void setTextQualifier(const QChar& c);
    void setBackslashSyntax(bool set);
    int getFileSize() const;
    int getCsvRows() const;
    int getCsvCols() const;
    QString getStatus() const;
    CsvTable getCsvTable() const;

protected:
    CsvTable m_table;

private:
    QByteArray m_array;
    QBuffer m_csv;
    QChar m_ch;
    QChar m_comment;
    unsigned int m_currCol;
    unsigned int m_currRow;
    bool m_isBackslashSyntax;
    bool m_isEof;
    bool m_isFileLoaded;
    bool m_isGood;
    qint64 m_lastPos;
    int m_maxCols;
    QChar m_qualifier;
    QChar m_separator;
    QString m_statusMsg;
    QTextStream m_ts;

    void getChar(QChar& c);
    void ungetChar();
    void peek(QChar& c);
    void fillColumns();
    bool isQualifier(const QChar& c) const;
    bool processEscapeMark(QString& s, QChar c);
    bool isComment();
    bool isEmptyRow(const CsvRow& row) const;
    bool parseFile();
    void parseRecord();
    void parseField(CsvRow& row);
    void parseSimple(QString& s);
    void parseQuoted(QString& s);
    void parseEscaped(QString& s);
    void parseEscapedText(QString& s);
    bool readFile(QIODevice* device);
    void reset();
    void clear();
    bool skipEndline();
    void skipLine();
    void appendStatusMsg(const QString& s, bool isCritical = false);
};

#endif // CSVPARSER_H
