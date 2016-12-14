// IFC SDK : IFC2X3 C++ Early Classes  
// Copyright (C) 2009 CSTB
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full license is in Licence.txt file included with this 
// distribution or is available at :
//     http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.



#include <ifc2x3/IfcStructuralPointAction.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcStructuralAction.h>
#include <ifc2x3/Visitor.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcStructuralPointAction::IfcStructuralPointAction(Step::Id id, Step::SPFData *args) : IfcStructuralAction(id, args) {
}

IfcStructuralPointAction::~IfcStructuralPointAction() {
}

bool IfcStructuralPointAction::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcStructuralPointAction(this);
}

const std::string &IfcStructuralPointAction::type() const {
    return IfcStructuralPointAction::s_type.getName();
}

const Step::ClassType &IfcStructuralPointAction::getClassType() {
    return IfcStructuralPointAction::s_type;
}

const Step::ClassType &IfcStructuralPointAction::getType() const {
    return IfcStructuralPointAction::s_type;
}

bool IfcStructuralPointAction::isOfType(const Step::ClassType &t) const {
    return IfcStructuralPointAction::s_type == t ? true : IfcStructuralAction::isOfType(t);
}

bool IfcStructuralPointAction::init() {
    bool status = IfcStructuralAction::init();
    std::string arg;
    if (!status) {
        return false;
    }
    return true;
}

void IfcStructuralPointAction::copy(const IfcStructuralPointAction &obj, const CopyOp &copyop) {
    IfcStructuralAction::copy(obj, copyop);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcStructuralPointAction::s_type("IfcStructuralPointAction");
