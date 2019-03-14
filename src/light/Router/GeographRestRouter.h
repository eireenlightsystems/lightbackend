#ifndef GEOGRAPHRESTROUTER_H
#define GEOGRAPHRESTROUTER_H

#include "RestRouter.h"

namespace light {

template <>
QString RestRouter<Geograph>::getPath() const;

template <>
QHttpServerResponse RestRouter<Geograph>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QList<QHttpServerRequest::Method> RestRouter<Geograph>::getAccessibleMethods() const;

} // namespace light

#endif // GEOGRAPHRESTROUTER_H
