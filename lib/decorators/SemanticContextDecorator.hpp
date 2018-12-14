// Copyright (c) Microsoft. All rights reserved.

#pragma once
#include "IDecorator.hpp"
#include "api/ContextFieldsProvider.hpp"

namespace ARIASDK_NS_BEGIN {

    class SemanticContextDecorator : public DecoratorBase {

    protected:
        ContextFieldsProvider& provider;

    public:
        SemanticContextDecorator(ILogManager& owner) :
            DecoratorBase(owner),
            provider(static_cast<ContextFieldsProvider&>(m_owner.GetSemanticContext()))
        {
        }

        SemanticContextDecorator(ILogManager& owner, ContextFieldsProvider& context) :
            DecoratorBase(owner),
            provider(context)
        {
        }

        bool decorate(::AriaProtocol::Record& record)
        {
            provider.writeToRecord(record);
            return true;
        }

    };


} ARIASDK_NS_END
