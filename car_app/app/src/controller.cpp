/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDebug>

#include <behaviortree_cpp_v3/bt_factory.h>

using namespace std;
using namespace BT;

constexpr auto TICK_INTERVAL = 20; // ms


Controller::Controller(QObject *parent)
    : QObject(parent), m_factory(make_unique<BehaviorTreeFactory>()), m_tree(make_unique<Tree>())
{
    // some registering stuff here

    connect(&m_tickTimer, &QTimer::timeout, this, &Controller::tickTree);
}

Controller::~Controller() {}

bool Controller::makeTreeFromFile(const std::string &filename)
{
    try {
        m_tree = make_unique<Tree>(move(m_factory->createTreeFromFile(filename)));
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

bool Controller::makeTreeFromText(const std::string &text)
{
    try {
        m_tree = make_unique<Tree>(move(m_factory->createTreeFromText(text)));
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

void Controller::start()
{
    m_tickTimer.start(TICK_INTERVAL);
}

void Controller::stop()
{
    m_tickTimer.stop();
}

void Controller::tickTree()
{
    m_tree->tickRoot();
}
