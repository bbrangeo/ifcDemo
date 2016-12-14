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



#include <ifc2x3/IfcFlowMovingDeviceType.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcDistributionFlowElementType.h>
#include <ifc2x3/Visitor.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcFlowMovingDeviceType::IfcFlowMovingDeviceType(Step::Id id, Step::SPFData *args) : IfcDistributionFlowElementType(id, args) {
}

IfcFlowMovingDeviceType::~IfcFlowMovingDeviceType() {
}

bool IfcFlowMovingDeviceType::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcFlowMovingDeviceType(this);
}

const std::string &IfcFlowMovingDeviceType::type() const {
    return IfcFlowMovingDeviceType::s_type.getName();
}

const Step::ClassType &IfcFlowMovingDeviceType::getClassType() {
    return IfcFlowMovingDeviceType::s_type;
}

const Step::ClassType &IfcFlowMovingDeviceType::getType() const {
    return IfcFlowMovingDeviceType::s_type;
}

bool IfcFlowMovingDeviceType::isOfType(const Step::ClassType &t) const {
    return IfcFlowMovingDeviceType::s_type == t ? true : IfcDistributionFlowElementType::isOfType(t);
}

bool IfcFlowMovingDeviceType::init() {
    bool status = IfcDistributionFlowElementType::init();
    std::string arg;
    if (!status) {
        return false;
    }
    return true;
}

void IfcFlowMovingDeviceType::copy(const IfcFlowMovingDeviceType &obj, const CopyOp &copyop) {
    IfcDistributionFlowElementType::copy(obj, copyop);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcFlowMovingDeviceType::s_type("IfcFlowMovingDeviceType");
