#ifndef SERIESFILTER_H
#define SERIESFILTER_H

#include "komga_api_global.h"
#include <QObject>
#include <QVariantList>

class KOMGA_API_EXPORT SeriesFilter: public QObject
{
    Q_OBJECT
    Q_PROPERTY( QVariantList ui_seriesFilterTags READ filterTags WRITE setFilterTags NOTIFY filterTagsChanged )
    Q_PROPERTY( QVariantList ui_seriesFilterGenres READ filterGenres WRITE setFilterGenres NOTIFY filterGenresChanged )
    Q_PROPERTY( QVariantList ui_seriesFilterAgeRatings READ filterAgeRatings WRITE setFilterAgeRatings NOTIFY filterAgeRatingsChanged )
    Q_PROPERTY( QVariantList ui_seriesFilterLanguages READ filterLanguages WRITE setFilterLanguages NOTIFY filterLanguagesChanged )
    Q_PROPERTY( QVariantList ui_seriesFilterPublishers READ filterPublishers WRITE setFilterPublishers NOTIFY filterPublishersChanged )

public:
    SeriesFilter(QObject *parent = nullptr);
    void addStatus(QString &status);
    void removeStatus(QString &status);
    void addReadStatus(QString &status);
    void removeReadStatus(QString &status);
    void addTagFilter(QString &tag);
    void removeTagFilter(QString &tag);
    void addGenreFilter(QString &genre);
    void removeGenreFilter(QString &genre);
    void addAgeRatingFilter(QString &rating);
    void removeAgeRatingFilter(QString &rating);
    void addLanguageFilter(QString &language);
    void removeLanguageFilter(QString &language);
    void addPublisherFilter(QString &publisher);
    void removePublisherFilter(QString &publisher);

    QList<QString> filterStatuses() const;
    void setFilterStatuses(const QList<QString> &filterStatuses);

    QList<QString> filterReadStatuses() const;
    void setFilterReadStatuses(const QList<QString> &filterReadStatuses);

    QVariantList filterTags() const;
    void setFilterTags(const QVariantList &filterTags);

    QList<QString> appliedTags() const;

    QList<QString> appliedGenres() const;

    QVariantList filterGenres() const;
    void setFilterGenres(const QVariantList &filterGenres);

    QList<QString> appliedAgeRatings() const;

    QVariantList filterAgeRatings() const;
    void setFilterAgeRatings(const QVariantList &filterAgeRatings);

    QList<QString> appliedLanguages() const;

    QList<QString> appliedPublishers() const;

    QVariantList filterLanguages() const;
    void setFilterLanguages(const QVariantList &filterLanguages);

    QVariantList filterPublishers() const;
    void setFilterPublishers(const QVariantList &filterPublishers);

signals:
    void filtersChanged();
    void filterTagsChanged(QVariantList tags);
    void filterGenresChanged(QVariantList genres);
    void filterAgeRatingsChanged(QVariantList ageRatings);
    void filterLanguagesChanged(QVariantList languages);
    void filterPublishersChanged(QVariantList publishers);

private:
    QList<QString> m_filterStatuses{};
    QList<QString> m_filterReadStatuses{};
    QList<QString> m_filterTags{};
    QList<QString> m_appliedTags{};
    QList<QString> m_filterGenres{};
    QList<QString> m_appliedGenres{};
    QList<QString> m_filterAgeRatings{};
    QList<QString> m_appliedAgeRatings{};
    QList<QString> m_filterLanguages{};
    QList<QString> m_appliedLanguages{};
    QList<QString> m_filterPublishers{};
    QList<QString> m_appliedPublishers{};

};

#endif // SERIESFILTER_H
