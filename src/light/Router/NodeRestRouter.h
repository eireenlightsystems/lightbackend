#ifndef NODERESTROUTER_H
#define NODERESTROUTER_H

#include "RestRouter.h"

namespace light {

struct NodeCoordinate
{
};

template <>
QString RestRouter<Node>::getPath() const;

template <>
QHttpServerResponse RestRouter<Node>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<Node>::post(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<Node>::patch(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<Node>::del(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QString RestRouter<NodeCoordinate>::getPath() const;

template <>
QHttpServerResponse RestRouter<NodeCoordinate>::patch(const SessionShared& session,
						      const QHttpServerRequest& req) const;

} // namespace light

#endif // NODERESTROUTER_H
