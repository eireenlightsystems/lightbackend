#ifndef NODETYPECONTROLLER_H
#define NODETYPECONTROLLER_H

#include "Controller.h"
#include "NodeType.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<NodeType, Crud> : public EditableController<NodeType, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<NodeType, Crud>::ins(const QList<QVariantHash>& params) {
    NodeTypeSharedList newNodeTypes;
    for (const auto& param : params){
        auto newNodeType = NodeTypeShared::create();

        if (param.contains("code")) {
          QString code = param.value("code").toString();
          newNodeType->setCode(code);
        }

        if (param.contains("name")) {
          QString name = param.value("name").toString();
          newNodeType->setName(name);
        }

        if (param.contains("model")) {
          QString model = param.value("model").toString();
          newNodeType->setModel(model);
        }

	if (param.contains("comments")) {
	  QString comment = param.value("comments").toString();
          newNodeType->setComment(comment);
        }

        if (param.contains("height")) {
          double height = param.value("height").toDouble();
          newNodeType->setHeight(height);
        }

        newNodeTypes << newNodeType;
    }

    Crud<NodeType> nodeTypeCrud;
    nodeTypeCrud.setSession(this->getSession());
    nodeTypeCrud.save(newNodeTypes);
    IDList result;
    std::transform(newNodeTypes.begin(), newNodeTypes.end(), std::back_inserter(result), [](const NodeTypeShared& nodeType) {
      return nodeType->getId();
    });
    return result;
}

template <template <typename> class Crud>
void Controller<NodeType, Crud>::upd(const QList<QVariantHash>& params) {
  NodeTypeSharedList nodeTypes;
  Crud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID nodeTypeId = param.value("id").value<ID>();
    auto nodeType = nodeTypeCrud.selById(nodeTypeId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      nodeType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      nodeType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      nodeType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      nodeType->setComment(comment);
    }

    if (param.contains("height")) {
      double height = param.value("height").toDouble();
      nodeType->setHeight(height);
    }

    nodeTypes << nodeType;
  }

  nodeTypeCrud.save(nodeTypes);
}

template <template <typename> class Crud>
void Controller<NodeType, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // NODETYPECONTROLLER_H
