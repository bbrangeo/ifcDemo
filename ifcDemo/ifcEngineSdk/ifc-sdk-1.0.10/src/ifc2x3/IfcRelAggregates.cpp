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



#include <ifc2x3/IfcRelAggregates.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcRelDecomposes.h>
#include <ifc2x3/Visitor.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcRelAggregates::IfcRelAggregates(Step::Id id, Step::SPFData *args) : IfcRelDecomposes(id, args) {
}

IfcRelAggregates::~IfcRelAggregates() {
}

bool IfcRelAggregates::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcRelAggregates(this);
}

const std::string &IfcRelAggregates::type() const {
    return IfcRelAggregates::s_type.getName();
}

const Step::ClassType &IfcRelAggregates::getClassType() {
    return IfcRelAggregates::s_type;
}

const Step::ClassType &IfcRelAggregates::getType() const {
    return IfcRelAggregates::s_type;
}

bool IfcRelAggregates::isOfType(const Step::ClassType &t) const {
    return IfcRelAggregates::s_type == t ? true : IfcRelDecomposes::isOfType(t);
}

bool IfcRelAggregates::init() {
    bool status = IfcRelDecomposes::init();
    std::string arg;
    if (!status) {
        return false;
    }
    return true;
}

void IfcRelAggregates::copy(const IfcRelAggregates &obj, const CopyOp &copyop) {
    IfcRelDecomposes::copy(obj, copyop);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcRelAggregates::s_type("IfcRelAggregates");
