#include <scope/action.h>
#include <unity/scopes/ActivationResponse.h>
#include <unity/UnityExceptions.h>

#include <QString>
#include <QDebug>

#include <iostream>

namespace sc = unity::scopes;
using namespace std;

QString qstr_(std::string str)
{
    return QString::fromStdString(str);
}

Action::Action(const unity::scopes::Result &result,
               const unity::scopes::ActionMetadata &metadata,
               std::string const& widget_id,
               std::string const& action_id,
               scope::Scope & scope)
    : result_(result),
      scope_(scope),
      sc::ActivationQueryBase(result, metadata, widget_id, action_id)
{
}

sc::ActivationResponse Action::activate()
{
    qDebug() << "action id in activate: " << qstr_(action_id());

    QString review = QString("%1").arg(qstr_(action_metadata().scope_data().
                                              get_dict()["review"].get_string()));

    double rating = action_metadata().scope_data().
                          get_dict()["rating"].get_double();

    qDebug() << "review: " << review;
    qDebug() << "rating: " << rating;

    sc::ActivationResponse done(sc::ActivationResponse::ShowDash);
    cerr << "activate called" << endl;

    try {
        std::string val = result_["get_previous"].get_string();
        qDebug() << "PREVIOUS button is clicked!";
        us::CannedQuery cq("scopetemplates.xiaoguo_scopetemplates");
        // restore the previous search
//        cq.set_filter_state(scope_.filter_state);
//        cq.set_query_string(scope_.previous_query);
        return us::ActivationResponse(cq);
    }
    catch ( unity::LogicException &e){
    }

    try {
        std::string val = result_["get_next"].get_string();
        qDebug() << "NEXT button is clicked!";
        us::CannedQuery cq("scopetemplates.xiaoguo_scopetemplates");
        // restore the previous search
//        cq.set_filter_state(scope_.filter_state);
//        if (scope_.previous_query.empty())
//            cq.set_department_id(scope_.previous_dept_id);
//        cq.set_query_string("");
        return us::ActivationResponse(cq);
    }
    catch ( unity::LogicException &e){
    }

    try {
        std::string val = result_["go_to_top"].get_string();
        qDebug() << "GO_TO_TOP button is clicked!";
        us::CannedQuery cq("com.canonical.scopes.500pxphotoscope_500pxphotoscope");
//        cq.set_filter_state(scope_.filter_state);
//        if (scope_.previous_query.empty())
//            cq.set_department_id(scope_.previous_dept_id);
//        cq.set_query_string(scope_.previous_query);
        return us::ActivationResponse(cq);
    }
    catch ( unity::LogicException &e){
    }

    return done;
}
