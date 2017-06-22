#include "DebugEvents.hpp"
#include "utils/Utils.hpp"
#include "pal/PAL.hpp"

#include <atomic>

namespace ARIASDK_NS_BEGIN {

        /// <summary>Add event listener for specific debug event type.</summary>
        void DebugEventSource::AddEventListener(DebugEventType type, DebugEventListener &listener)
        {
            auto &v = listeners[type];
            v.push_back(&listener);
        }

        /// <summary>Remove previously added debug event listener for specific type.</summary>
        void DebugEventSource::RemoveEventListener(DebugEventType type, DebugEventListener &listener)
        {
            auto &v = listeners[type];
            auto it = std::remove(v.begin(), v.end(), &listener);
            v.erase(it, v.end());
        }

        /// <summary>ARIA SDK invokes this method to dispatch event to client callback</summary>
        bool DebugEventSource::DispatchEvent(DebugEventType type)
        {
            DebugEvent evt;
            evt.type = type;
            return DispatchEvent(evt);
        }

        /// <summary>ARIA SDK invokes this method to dispatch event to client callback</summary>
        bool DebugEventSource::DispatchEvent(DebugEvent &evt)
        {
            seq++;
            evt.seq = seq.load();
            evt.ts = PAL::getUtcSystemTime();
            bool dispatched = false;

            if (listeners.size()) {
                // Events filter handlers list
                auto &v = listeners[evt.type];
                for (auto listener : v) {
                    listener->OnDebugEvent(evt);
                    dispatched = true;
                }
            }

            return dispatched;
        }

} ARIASDK_NS_END
