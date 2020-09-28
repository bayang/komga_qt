#include "seriesfilter.h"

SeriesFilter::SeriesFilter(QObject *parent): QObject{parent}

{

}

void SeriesFilter::addStatus(QString &status)
{
    if (! m_filterStatuses.contains(status)) {
        m_filterStatuses.append(status);
        emit filtersChanged();
    }
}

void SeriesFilter::removeStatus(QString &status)
{
    if (m_filterStatuses.contains(status)) {
        m_filterStatuses.removeAll(status);
        emit filtersChanged();
    }
}

void SeriesFilter::addReadStatus(QString &status)
{
    if (! m_filterReadStatuses.contains(status)) {
        m_filterReadStatuses.append(status);
        emit filtersChanged();
    }
}

void SeriesFilter::removeReadStatus(QString &status)
{
    if (m_filterReadStatuses.contains(status)) {
        m_filterReadStatuses.removeAll(status);
        emit filtersChanged();
    }
}

void SeriesFilter::addTagFilter(QString &tag)
{
    if (! m_appliedTags.contains(tag)) {
        m_appliedTags.append(tag);
        emit filtersChanged();
    }
}

void SeriesFilter::removeTagFilter(QString &tag)
{
    if (m_appliedTags.contains(tag)){
        m_appliedTags.removeAll(tag);
        emit filtersChanged();
    }
}

void SeriesFilter::addGenreFilter(QString &genre)
{
    if (! m_appliedGenres.contains(genre)) {
        m_appliedGenres.append(genre);
        emit filtersChanged();
    }
}

void SeriesFilter::removeGenreFilter(QString &genre)
{
    if (m_appliedGenres.contains(genre)) {
        m_appliedGenres.removeAll(genre);
        emit filtersChanged();
    }
}

void SeriesFilter::addAgeRatingFilter(QString &rating)
{
    if (! m_appliedAgeRatings.contains(rating)) {
        m_appliedAgeRatings.append(rating);
        emit filtersChanged();
    }
}

void SeriesFilter::removeAgeRatingFilter(QString &rating)
{
    if (m_appliedAgeRatings.contains(rating)) {
        m_appliedAgeRatings.removeAll(rating);
        emit filtersChanged();
    }
}

void SeriesFilter::addLanguageFilter(QString &language)
{
    if (! m_appliedLanguages.contains(language)) {
        m_appliedLanguages.append(language);
        emit filtersChanged();
    }
}

void SeriesFilter::removeLanguageFilter(QString &language)
{
    if (m_appliedLanguages.contains(language)) {
        m_appliedLanguages.removeAll(language);
        emit filtersChanged();
    }
}

void SeriesFilter::addPublisherFilter(QString &publisher)
{
    if (! m_appliedPublishers.contains(publisher)) {
        m_appliedPublishers.append(publisher);
        emit filtersChanged();
    }
}

void SeriesFilter::removePublisherFilter(QString &publisher)
{
    if (m_appliedPublishers.contains(publisher)) {
        m_appliedPublishers.removeAll(publisher);
        emit filtersChanged();
    }
}

QList<QString> SeriesFilter::filterStatuses() const
{
    return m_filterStatuses;
}

void SeriesFilter::setFilterStatuses(const QList<QString> &filterStatuses)
{
    m_filterStatuses = filterStatuses;
}

QList<QString> SeriesFilter::filterReadStatuses() const
{
    return m_filterReadStatuses;
}

void SeriesFilter::setFilterReadStatuses(const QList<QString> &filterReadStatuses)
{
    m_filterReadStatuses = filterReadStatuses;
}

QVariantList SeriesFilter::filterTags() const
{
    QVariantList l;
    for (auto val : m_filterTags) {
        l.append(val);
    }
    return l;
}

void SeriesFilter::setFilterTags(const QVariantList &filterTags)
{
    QList<QString> tags{};
    for (QVariant t : filterTags){
        tags.append(t.toString());
    }
    m_filterTags = tags;
    emit filterTagsChanged(filterTags);
}

QList<QString> SeriesFilter::appliedTags() const
{
    return m_appliedTags;
}

QList<QString> SeriesFilter::appliedGenres() const
{
    return m_appliedGenres;
}

QVariantList SeriesFilter::filterGenres() const
{
    QVariantList l;
    for (auto val : m_filterGenres) {
        l.append(val);
    }
    return l;
}

void SeriesFilter::setFilterGenres(const QVariantList &filterGenres)
{
    QList<QString> genres{};
    for (QVariant t : filterGenres){
        genres.append(t.toString());
    }
    m_filterGenres = genres;
    emit filterGenresChanged(filterGenres);
}

QList<QString> SeriesFilter::appliedAgeRatings() const
{
    return m_appliedAgeRatings;
}

QVariantList SeriesFilter::filterAgeRatings() const
{
    QVariantList l;
    for (auto val : m_filterAgeRatings) {
        l.append(val);
    }
    return l;
}

void SeriesFilter::setFilterAgeRatings(const QVariantList &filterAgeRatings)
{
    QList<QString> ratings{};
    for (QVariant t : filterAgeRatings){
        ratings.append(t.toString());
    }
    m_filterAgeRatings = ratings;
    emit filterAgeRatingsChanged(filterAgeRatings);
}

QList<QString> SeriesFilter::appliedLanguages() const
{
    return m_appliedLanguages;
}

QList<QString> SeriesFilter::appliedPublishers() const
{
    return m_appliedPublishers;
}

QVariantList SeriesFilter::filterLanguages() const
{
    QVariantList l;
    for (auto val : m_filterLanguages) {
        l.append(val);
    }
    return l;
}

void SeriesFilter::setFilterLanguages(const QVariantList &filterLanguages)
{
    QList<QString> languages{};
    for (QVariant t : filterLanguages){
        languages.append(t.toString());
    }
    m_filterLanguages = languages;
    emit filterLanguagesChanged(filterLanguages);
}

QVariantList SeriesFilter::filterPublishers() const
{
    QVariantList l;
    for (auto val : m_filterPublishers) {
        l.append(val);
    }
    return l;
}

void SeriesFilter::setFilterPublishers(const QVariantList &filterPublishers)
{
    QList<QString> publishers{};
    for (QVariant t : filterPublishers){
        publishers.append(t.toString());
    }
    m_filterPublishers = publishers;
    emit filterPublishersChanged(filterPublishers);
}
