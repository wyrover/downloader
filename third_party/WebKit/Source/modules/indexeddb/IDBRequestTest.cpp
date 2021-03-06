/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "modules/indexeddb/IDBRequest.h"

#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/V8Binding.h"
#include "bindings/core/v8/V8BindingForTesting.h"
#include "core/dom/DOMException.h"
#include "core/dom/ExceptionCode.h"
#include "core/dom/ExecutionContext.h"
#include "core/testing/NullExecutionContext.h"
#include "modules/indexeddb/IDBDatabaseCallbacks.h"
#include "modules/indexeddb/IDBKey.h"
#include "modules/indexeddb/IDBOpenDBRequest.h"
#include "modules/indexeddb/IDBValue.h"
#include "modules/indexeddb/MockWebIDBDatabase.h"
#include "platform/SharedBuffer.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "wtf/OwnPtr.h"
#include "wtf/PassOwnPtr.h"
#include "wtf/PassRefPtr.h"
#include "wtf/Vector.h"
#include "wtf/dtoa/utils.h"
#include <v8.h>

namespace blink {
namespace {

class IDBRequestTest : public testing::Test {
public:
    IDBRequestTest()
        : m_scope(v8::Isolate::GetCurrent())
    {
    }

    void SetUp() override
    {
        m_executionContext = new NullExecutionContext();
        m_scope.getScriptState()->setExecutionContext(m_executionContext.get());
    }

    void TearDown() override
    {
        m_executionContext->notifyContextDestroyed();
        m_scope.getScriptState()->setExecutionContext(nullptr);
    }

    v8::Isolate* isolate() const { return m_scope.isolate(); }
    ScriptState* getScriptState() const { return m_scope.getScriptState(); }
    ExecutionContext* getExecutionContext() const { return m_scope.getScriptState()->getExecutionContext(); }

private:
    V8TestingScope m_scope;
    Persistent<ExecutionContext> m_executionContext;
};

TEST_F(IDBRequestTest, EventsAfterStopping)
{
    IDBTransaction* transaction = nullptr;
    IDBRequest* request = IDBRequest::create(getScriptState(), IDBAny::createUndefined(), transaction);
    EXPECT_EQ(request->readyState(), "pending");
    getExecutionContext()->stopActiveDOMObjects();

    // Ensure none of the following raise assertions in stopped state:
    request->onError(DOMException::create(AbortError, "Description goes here."));
    request->onSuccess(Vector<String>());
    request->onSuccess(nullptr, IDBKey::createInvalid(), IDBKey::createInvalid(), IDBValue::create());
    request->onSuccess(IDBKey::createInvalid());
    request->onSuccess(IDBValue::create());
    request->onSuccess(static_cast<int64_t>(0));
    request->onSuccess();
    request->onSuccess(IDBKey::createInvalid(), IDBKey::createInvalid(), IDBValue::create());
}

TEST_F(IDBRequestTest, AbortErrorAfterAbort)
{
    IDBTransaction* transaction = nullptr;
    IDBRequest* request = IDBRequest::create(getScriptState(), IDBAny::createUndefined(), transaction);
    EXPECT_EQ(request->readyState(), "pending");

    // Simulate the IDBTransaction having received onAbort from back end and aborting the request:
    request->abort();

    // Now simulate the back end having fired an abort error at the request to clear up any intermediaries.
    // Ensure an assertion is not raised.
    request->onError(DOMException::create(AbortError, "Description goes here."));

    // Stop the request lest it be GCed and its destructor
    // finds the object in a pending state (and asserts.)
    getExecutionContext()->stopActiveDOMObjects();
}

TEST_F(IDBRequestTest, ConnectionsAfterStopping)
{
    const int64_t transactionId = 1234;
    const int64_t version = 1;
    const int64_t oldVersion = 0;
    const IDBDatabaseMetadata metadata;
    Persistent<IDBDatabaseCallbacks> callbacks = IDBDatabaseCallbacks::create();

    {
        OwnPtr<MockWebIDBDatabase> backend = MockWebIDBDatabase::create();
        EXPECT_CALL(*backend, abort(transactionId))
            .Times(1);
        EXPECT_CALL(*backend, close())
            .Times(1);
        IDBOpenDBRequest* request = IDBOpenDBRequest::create(getScriptState(), callbacks, transactionId, version);
        EXPECT_EQ(request->readyState(), "pending");

        getExecutionContext()->stopActiveDOMObjects();
        request->onUpgradeNeeded(oldVersion, backend.release(), metadata, WebIDBDataLossNone, String());
    }

    {
        OwnPtr<MockWebIDBDatabase> backend = MockWebIDBDatabase::create();
        EXPECT_CALL(*backend, close())
            .Times(1);
        IDBOpenDBRequest* request = IDBOpenDBRequest::create(getScriptState(), callbacks, transactionId, version);
        EXPECT_EQ(request->readyState(), "pending");

        getExecutionContext()->stopActiveDOMObjects();
        request->onSuccess(backend.release(), metadata);
    }
}

} // namespace
} // namespace blink
