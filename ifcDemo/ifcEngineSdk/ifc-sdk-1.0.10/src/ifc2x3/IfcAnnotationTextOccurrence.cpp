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



#include <ifc2x3/IfcAnnotationTextOccurrence.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcAnnotationOccurrence.h>
#include <ifc2x3/Visitor.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcAnnotationTextOccurrence::IfcAnnotationTextOccurrence(Step::Id id, Step::SPFData *args) : IfcAnnotationOccurrence(id, args) {
}

IfcAnnotationTextOccurrence::~IfcAnnotationTextOccurrence() {
}

bool IfcAnnotationTextOccurrence::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcAnnotationTextOccurrence(this);
}

const std::string &IfcAnnotationTextOccurrence::type() const {
    return IfcAnnotationTextOccurrence::s_type.getName();
}

const Step::ClassType &IfcAnnotationTextOccurrence::getClassType() {
    return IfcAnnotationTextOccurrence::s_type;
}

const Step::ClassType &IfcAnnotationTextOccurrence::getType() const {
    return IfcAnnotationTextOccurrence::s_type;
}

bool IfcAnnotationTextOccurrence::isOfType(const Step::ClassType &t) const {
    return IfcAnnotationTextOccurrence::s_type == t ? true : IfcAnnotationOccurrence::isOfType(t);
}

bool IfcAnnotationTextOccurrence::init() {
    bool status = IfcAnnotationOccurrence::init();
    std::string arg;
    if (!status) {
        return false;
    }
    return true;
}

void IfcAnnotationTextOccurrence::copy(const IfcAnnotationTextOccurrence &obj, const CopyOp &copyop) {
    IfcAnnotationOccurrence::copy(obj, copyop);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcAnnotationTextOccurrence::s_type("IfcAnnotationTextOccurrence");
