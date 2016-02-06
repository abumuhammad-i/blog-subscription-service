/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2016 Mohammad S. Babaei
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Manage website pages.
 */


#include <boost/exception/diagnostic_information.hpp>
#include <boost/format.hpp>
#include <cppdb/frontend.h>
#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WWidget>
#include <CoreLib/Crypto.hpp>
#include <CoreLib/Database.hpp>
#include <CoreLib/FileSystem.hpp>
#include <CoreLib/Log.hpp>
#include "CgiEnv.hpp"
#include "CgiRoot.hpp"
#include "CmsSubscribers.hpp"
#include "Div.hpp"
#include "Pool.hpp"

using namespace std;
using namespace Wt;
using namespace Service;

#define         UNKNOWN_ERROR       "Unknown error!"

struct CmsSubscribers::Impl : public Wt::WObject
{
public:
    WContainerWidget *SubscribersTableContainer;

public:
    Impl();
    ~Impl();

public:
    void OnAllButtonPressed();
    void OnEnFaButtonPressed();
    void OnEnButtonPressed();
    void OnFaButtonPressed();
};

CmsSubscribers::CmsSubscribers()
    : Page(),
    m_pimpl(make_unique<CmsSubscribers::Impl>())
{
    this->clear();
    this->setId("CmsSubscribersPage");
    this->addWidget(Layout());
}

CmsSubscribers::~CmsSubscribers() = default;

WWidget *CmsSubscribers::Layout()
{
    Div *container = new Div("CmsSubscribers", "container-fluid");

    try {
        CgiRoot *cgiRoot = static_cast<CgiRoot *>(WApplication::instance());
        CgiEnv *cgiEnv = cgiRoot->GetCgiEnvInstance();

        string htmlData;
        string file;
        if (cgiEnv->GetCurrentLanguage() == CgiEnv::Language::Fa) {
            file = "../templates/cms-subscribers-fa.wtml";
        } else {
            file = "../templates/cms-subscribers.wtml";
        }

        if (CoreLib::FileSystem::Read(file, htmlData)) {
            /// Fill the template
            WTemplate *tmpl = new WTemplate(container);
            tmpl->setTemplateText(WString(htmlData), TextFormat::XHTMLUnsafeText);

            WPushButton *allSubscribersPushButton = new WPushButton(tr("cms-subscribers-all"));
            allSubscribersPushButton->setStyleClass("btn btn-default");

            WPushButton *englishFarsiSubscribersPushButton = new WPushButton(tr("cms-subscribers-english-farsi"));
            englishFarsiSubscribersPushButton->setStyleClass("btn btn-default");

            WPushButton *englishSubscribersPushButton = new WPushButton(tr("cms-subscribers-english"));
            englishSubscribersPushButton->setStyleClass("btn btn-default");

            WPushButton *farsiPushButton = new WPushButton(tr("cms-subscribers-farsi"));
            farsiPushButton->setStyleClass("btn btn-default");

            m_pimpl->SubscribersTableContainer = new Div("SubscribersTableContainer", "subscribers-table-container");

            tmpl->bindWidget("subscribers-title", new WText(tr("cms-subscribers-page-title")));

            tmpl->bindWidget("subscribers-table", m_pimpl->SubscribersTableContainer);

            tmpl->bindWidget("all-subscribers-button", allSubscribersPushButton);
            tmpl->bindWidget("english-farsi-subscribers-button", englishFarsiSubscribersPushButton);
            tmpl->bindWidget("english-subscribers-button", englishSubscribersPushButton);
            tmpl->bindWidget("farsi-subscribers-button", farsiPushButton);



            allSubscribersPushButton->setFocus();
        }
    }

    catch (boost::exception &ex) {
        LOG_ERROR(boost::diagnostic_information(ex));
    }

    catch (std::exception &ex) {
        LOG_ERROR(ex.what());
    }

    catch (...) {
        LOG_ERROR(UNKNOWN_ERROR);
    }

    return container;
}

CmsSubscribers::Impl::Impl()
{

}

CmsSubscribers::Impl::~Impl() = default;

void CmsSubscribers::Impl::OnAllButtonPressed()
{

}

void CmsSubscribers::Impl::OnEnFaButtonPressed()
{

}

void CmsSubscribers::Impl::OnEnButtonPressed()
{

}

void CmsSubscribers::Impl::OnFaButtonPressed()
{

}

