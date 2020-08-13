#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>
#include "komga_api_global.h"
#include "book.h"
#include "series.h"
#include "collection.h"

class KOMGA_API_EXPORT SearchResult : public QObject
{
    Q_OBJECT

public:
    explicit SearchResult(QObject *parent = nullptr);
    enum ResultType {
        SeriesType,
        BookType,
        CollectionType
    };
    Q_ENUM(ResultType);
    QString id() const;
    void setId(QString id);

    QString name() const;
    void setName(const QString &name);

    ResultType resultType() const;
    void setResultType(const ResultType &resultType);

    Book *book() const;
    void setBook(Book *book);

    Series *series() const;
    void setSeries(Series *series);

    Collection *collection() const;
    void setCollection(Collection *collection);

private:
    QString m_id {};
    QString m_name{};
    ResultType m_resultType{};
    Book *m_book{};
    Series* m_series{};
    Collection* m_collection{};

};

#endif // SEARCHRESULT_H
