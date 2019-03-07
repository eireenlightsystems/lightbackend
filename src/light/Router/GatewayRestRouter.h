#ifndef GATEWAYRESTROUTER_H
#define GATEWAYRESTROUTER_H

#include "RestRouter.h"

namespace light {

template<>
QString RestRouter<Gateway>::getPath() const;

template<>
QHttpServerResponse RestRouter<Gateway>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QHttpServerResponse RestRouter<Gateway>::post(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QHttpServerResponse RestRouter<Gateway>::patch(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QHttpServerResponse RestRouter<Gateway>::del(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QString RestRouter<EquipmentOwner>::getPath() const;

template<>
QHttpServerResponse RestRouter<EquipmentOwner>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QList<QHttpServerRequest::Method> RestRouter<EquipmentOwner>::getAsseccibleMethods() const;

template<>
QString RestRouter<GatewayType>::getPath() const;

template<>
QHttpServerResponse RestRouter<GatewayType>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QList<QHttpServerRequest::Method> RestRouter<GatewayType>::getAsseccibleMethods() const;

} // namespace light

#endif // GATEWAYRESTROUTER_H
