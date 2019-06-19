/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2018-2019 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_PROPERTYCEFSYNCHRONIZER_H
#define IVW_PROPERTYCEFSYNCHRONIZER_H

#include <modules/webbrowser/webbrowsermoduledefine.h>
#include <modules/webbrowser/properties/propertywidgetcef.h>

#include <inviwo/core/properties/property.h>
#include <inviwo/core/properties/propertyownerobserver.h>
#include <inviwo/core/properties/propertywidgetfactory.h>
#include <inviwo/core/util/callback.h>

#include <warn/push>
#include <warn/ignore/all>
#include "include/wrapper/cef_message_router.h"
#include <include/cef_load_handler.h>
#include <warn/pop>

namespace inviwo {

/** \class PropertyCefSynchronizer
 *
 * Flow of information between PropertyWidgetCEF and browser.
 * Changes can start from Inviwo (left) or browser (right).
 * PropertyWidgetCEF::onQueryBlocker is used to prevent loops.
 *
 *     Inviwo           Browser (JavaScript)
 * Property change
 *        |
 * updateFromProperty()
 * onQueryBlocker_ += 1
 * ExecuteJavaScript()  --> set values
 *                          oninput()
 *                             |
 *                             |
 *     OnQuery  <---------  cefQuery
 * onQueryBlocker_ -= 1
 *   Deserialize
 *
 *
 */
#include <warn/push>
#include <warn/ignore/dll-interface-base>  // Fine if dependent libs use the same CEF lib binaries
class IVW_MODULE_WEBBROWSER_API PropertyCefSynchronizer
    : public CefMessageRouterBrowserSide::Handler,
      public CefLoadHandler,
      public PropertyOwnerObserver {
public:
    explicit PropertyCefSynchronizer();
    virtual ~PropertyCefSynchronizer() = default;

    /**
     * Synchronizes all widgets and sets their frame, called when frame has loaded.
     */
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                           int httpStatusCode) override;

    /**
     * Called due to cefQuery execution in message_router.html.
     * Expects the request for be a JSON-format. See inviwoapi.js:
     * {command: "subscribe", "path": propertyPath, "id":htmlId}
     * for synchronizing property to change.
     * {command: "property.set", "path":"PropertyIdentifier", "value":0.5}
     * for setting a value
     * {command: "property.get", "path": propertyPath}
     * for getting a value.
     * Currently only supports a single property in the request.
     * @see PropertyWidgetCEF
     */
    virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id,
                         const CefString& request, bool persistent,
                         CefRefPtr<Callback> callback) override;



    // Use own widget factory for now. Multiple widget types are not supported in Inviwo yet
    template <typename T, typename P>
    void registerPropertyWidget(PropertySemantics semantics);

    PropertyWidgetFactory htmlWidgetFactory_;

    // Remove widget if property is removed
    virtual void onWillRemoveProperty(Property* property, size_t index) override;

private:
    /**
     * Add property to synchronize.
     * Stops synchronizing property when this object
     * is destroyed, property is removed, or when stopSynchronize is called.
     * @param property Property to synchronize
     * @param onChange Callback to execute when the property changes.
     * @param propertyObserverCallback Callback to execute when on PropertyObserver notifications.
     */
    void startSynchronize(Property* property, std::string onChange, std::string propertyObserverCallback);
    /**
     * Stop property from being synchronized.
     * @param property Property to remove
     */
    void stopSynchronize(Property* property);
    std::vector<std::unique_ptr<PropertyWidgetFactoryObject>> propertyWidgets_;

    std::vector<std::unique_ptr<PropertyWidgetCEF>> widgets_;
    IMPLEMENT_REFCOUNTING(PropertyCefSynchronizer);
};
#include <warn/pop>

template <typename T, typename P>
void PropertyCefSynchronizer::registerPropertyWidget(PropertySemantics semantics) {
    auto propertyWidget = std::make_unique<PropertyWidgetFactoryObjectTemplate<T, P>>(semantics);
    if (htmlWidgetFactory_.registerObject(propertyWidget.get())) {
        propertyWidgets_.push_back(std::move(propertyWidget));
    }
}
}  // namespace inviwo

#endif  // IVW_PROPERTYCEFSYNCHRONIZER_H
