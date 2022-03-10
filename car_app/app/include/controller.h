/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/


#pragma once

#include <memory>

#include <QObject>
#include <QTimer>

#include <icontroller.h>


namespace BT {
class BehaviorTreeFactory;
class Tree;
} // BT


class Controller : public QObject, public IController
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    virtual bool makeTreeFromFile(const std::string &filename) override;
    virtual bool makeTreeFromText(const std::string &text) override;

    virtual void start() override;
    virtual void stop() override;

private slots:
    void tickTree();

private:
    std::unique_ptr<BT::BehaviorTreeFactory> m_factory;
    std::unique_ptr<BT::Tree> m_tree;
    QTimer m_tickTimer;
};
