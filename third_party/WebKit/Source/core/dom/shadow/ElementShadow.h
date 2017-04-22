/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ElementShadow_h
#define ElementShadow_h

#include "core/CoreExport.h"
#include "core/dom/shadow/InsertionPoint.h"
#include "core/dom/shadow/SelectRuleFeatureSet.h"
#include "core/dom/shadow/ShadowRoot.h"
#include "core/dom/shadow/SlotAssignment.h"
#include "platform/heap/Handle.h"
#include "wtf/DoublyLinkedList.h"
#include "wtf/HashMap.h"
#include "wtf/Noncopyable.h"

namespace blink {

class CORE_EXPORT ElementShadow final : public GarbageCollectedFinalized<ElementShadow> {
    WTF_MAKE_NONCOPYABLE(ElementShadow);
public:
    static RawPtr<ElementShadow> create();
    ~ElementShadow();

    Element* host() const;
    ShadowRoot& youngestShadowRoot() const { DCHECK(m_shadowRoots.head()); return *m_shadowRoots.head(); }
    ShadowRoot* oldestShadowRoot() const { return m_shadowRoots.tail(); }
    ElementShadow* containingShadow() const;

    ShadowRoot* shadowRootIfV1() const
    {
        if (isV1())
            return &youngestShadowRoot();
        return nullptr;
    }

    HTMLSlotElement* assignedSlotFor(const Node& node) const
    {
        DCHECK(m_slotAssignment);
        return m_slotAssignment->assignedSlotFor(node);
    }

    ShadowRoot& addShadowRoot(Element& shadowHost, ShadowRootType);

    bool hasSameStyles(const ElementShadow*) const;

    void attach(const Node::AttachContext&);
    void detach(const Node::AttachContext&);

    void willAffectSelector();
    const SelectRuleFeatureSet& ensureSelectFeatureSet();

    void distributeIfNeeded();
    void setNeedsDistributionRecalc();
    bool needsDistributionRecalc() const { return m_needsDistributionRecalc; }

    const InsertionPoint* finalDestinationInsertionPointFor(const Node*) const;
    const DestinationInsertionPoints* destinationInsertionPointsFor(const Node*) const;

    void didDistributeNode(const Node*, InsertionPoint*);

    bool isV1() const { return youngestShadowRoot().isV1(); };
    bool isOpenOrV0() const { return youngestShadowRoot().isOpenOrV0(); };

    DECLARE_TRACE();

private:
    ElementShadow();

#if !ENABLE(OILPAN)
    void removeDetachedShadowRoots();
#endif

    void distribute();
    void clearDistribution();

    void distributeV0();
    void distributeV1();

    void collectSelectFeatureSetFrom(ShadowRoot&);
    void distributeNodeChildrenTo(InsertionPoint*, ContainerNode*);

    bool needsSelectFeatureSet() const { return m_needsSelectFeatureSet; }
    void setNeedsSelectFeatureSet() { m_needsSelectFeatureSet = true; }

#if ENABLE(OILPAN)
    // The cost of |new| in Oilpan is lower than non-Oilpan.  We should reduce
    // the size of HashMap entry.
    typedef HeapHashMap<Member<const Node>, Member<DestinationInsertionPoints>> NodeToDestinationInsertionPoints;
#else
    typedef HashMap<const Node*, DestinationInsertionPoints> NodeToDestinationInsertionPoints;
#endif
    NodeToDestinationInsertionPoints m_nodeToInsertionPoints;

    SelectRuleFeatureSet m_selectFeatures;
    // FIXME: Oilpan: add a heap-based version of DoublyLinkedList<>.
    DoublyLinkedList<ShadowRoot> m_shadowRoots;
    bool m_needsDistributionRecalc;
    bool m_needsSelectFeatureSet;

    // TODO(hayato): ShadowRoot should be an owner of SlotAssigment
    Member<SlotAssignment> m_slotAssignment;
};

inline Element* ElementShadow::host() const
{
    DCHECK(!m_shadowRoots.isEmpty());
    return youngestShadowRoot().host();
}

inline ShadowRoot* Node::youngestShadowRoot() const
{
    if (!isElementNode())
        return 0;
    return toElement(this)->youngestShadowRoot();
}

inline ShadowRoot* Element::youngestShadowRoot() const
{
    if (ElementShadow* shadow = this->shadow())
        return &shadow->youngestShadowRoot();
    return 0;
}

inline ShadowRoot* Element::shadowRootIfV1() const
{
    if (ElementShadow* shadow = this->shadow())
        return shadow->shadowRootIfV1();
    return nullptr;
}

inline ElementShadow* ElementShadow::containingShadow() const
{
    if (ShadowRoot* parentRoot = host()->containingShadowRoot())
        return parentRoot->owner();
    return 0;
}

inline void ElementShadow::distributeIfNeeded()
{
    if (m_needsDistributionRecalc)
        distribute();
    m_needsDistributionRecalc = false;
}

} // namespace blink

#endif