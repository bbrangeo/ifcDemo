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



#include <ifc2x3/IfcFeatureElement.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcElement.h>
#include <ifc2x3/Visitor.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcFeatureElement::IfcFeatureElement(Step::Id id, Step::SPFData *args) : IfcElement(id, args) {
}

IfcFeatureElement::~IfcFeatureElement() {
}

bool IfcFeatureElement::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcFeatureElement(this);
}

const std::string &IfcFeatureElement::type() const {
    return IfcFeatureElement::s_type.getName();
}

const Step::ClassType &IfcFeatureElement::getClassType() {
    return IfcFeatureElement::s_type;
}

const Step::ClassType &IfcFeatureElement::getType() const {
    return IfcFeatureElement::s_type;
}

bool IfcFeatureElement::isOfType(const Step::ClassType &t) const {
    return IfcFeatureElement::s_type == t ? true : IfcElement::isOfType(t);
}

bool IfcFeatureElement::init() {
    bool status = IfcElement::init();
    std::string arg;
    if (!status) {
        return false;
    }
    return true;
}

void IfcFeatureElement::copy(const IfcFeatureElement &obj, const CopyOp &copyop) {
    IfcElement::copy(obj, copyop);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcFeatureElement::s_type("IfcFeatureElement");
