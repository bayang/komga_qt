#include "asyncimageprovider.h"
#include "asyncimageresponse.h"

AsyncImageProvider::AsyncImageProvider(Komga_api *api) :
    m_api{api}
{

}
QQuickImageResponse* AsyncImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize) {
    AsyncImageResponse *ar = new AsyncImageResponse(id, requestedSize, m_api);
    return ar;
}
