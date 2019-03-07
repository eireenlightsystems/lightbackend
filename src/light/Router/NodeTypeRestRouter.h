#ifndef NODETYPERESTROUTER_H
#define NODETYPERESTROUTER_H

#include "RestRouter.h"

namespace light {

template<>
QString RestRouter<NodeType>::getPath() const;

template<>
QHttpServerResponse RestRouter<NodeType>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template<>
QList<QHttpServerRequest::Method> RestRouter<NodeType>::getAsseccibleMethods() const;

} // namespace light

#endif // NODETYPERESTROUTER_H
