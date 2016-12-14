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



#include <ifc2x3/IfcFooting.h>

#include <ifc2x3/CopyOp.h>
#include <ifc2x3/IfcBuildingElement.h>
#include <ifc2x3/Visitor.h>
#include <Step/BaseObject.h>
#include <Step/ClassType.h>
#include <Step/logger.h>


#include <string>

#include "precompiled.h"

using namespace ifc2x3;

IfcFooting::IfcFooting(Step::Id id, Step::SPFData *args) : IfcBuildingElement(id, args) {
    m_predefinedType = IfcFootingTypeEnum_UNSET;
}

IfcFooting::~IfcFooting() {
}

bool IfcFooting::acceptVisitor(Step::BaseVisitor *visitor) {
    return static_cast< Visitor * > (visitor)->visitIfcFooting(this);
}

const std::string &IfcFooting::type() const {
    return IfcFooting::s_type.getName();
}

const Step::ClassType &IfcFooting::getClassType() {
    return IfcFooting::s_type;
}

const Step::ClassType &IfcFooting::getType() const {
    return IfcFooting::s_type;
}

bool IfcFooting::isOfType(const Step::ClassType &t) const {
    return IfcFooting::s_type == t ? true : IfcBuildingElement::isOfType(t);
}

IfcFootingTypeEnum IfcFooting::getPredefinedType() {
    if (Step::BaseObject::inited()) {
        return m_predefinedType;
    }
    else {
        return IfcFootingTypeEnum_UNSET;
    }
}

const IfcFootingTypeEnum IfcFooting::getPredefinedType() const {
    IfcFooting * deConstObject = const_cast< IfcFooting * > (this);
    return deConstObject->getPredefinedType();
}

void IfcFooting::setPredefinedType(IfcFootingTypeEnum value) {
    m_predefinedType = value;
}

void IfcFooting::unsetPredefinedType() {
    m_predefinedType = IfcFootingTypeEnum_UNSET;
}

bool IfcFooting::testPredefinedType() const {
    return getPredefinedType() != IfcFootingTypeEnum_UNSET;
}

bool IfcFooting::init() {
    bool status = IfcBuildingElement::init();
    std::string arg;
    if (!status) {
        return false;
    }
    arg = m_args->getNext();
    if (arg == "$" || arg == "*") {
        m_predefinedType = IfcFootingTypeEnum_UNSET;
    }
    else {
        if (arg == ".FOOTING_BEAM.") {
            m_predefinedType = IfcFootingTypeEnum_FOOTING_BEAM;
        }
        else if (arg == ".PAD_FOOTING.") {
            m_predefinedType = IfcFootingTypeEnum_PAD_FOOTING;
        }
        else if (arg == ".PILE_CAP.") {
            m_predefinedType = IfcFootingTypeEnum_PILE_CAP;
        }
        else if (arg == ".STRIP_FOOTING.") {
            m_predefinedType = IfcFootingTypeEnum_STRIP_FOOTING;
        }
        else if (arg == ".USERDEFINED.") {
            m_predefinedType = IfcFootingTypeEnum_USERDEFINED;
        }
        else if (arg == ".NOTDEFINED.") {
            m_predefinedType = IfcFootingTypeEnum_NOTDEFINED;
        }
    }
    return true;
}

void IfcFooting::copy(const IfcFooting &obj, const CopyOp &copyop) {
    IfcBuildingElement::copy(obj, copyop);
    setPredefinedType(obj.m_predefinedType);
    return;
}

IFC2X3_EXPORT Step::ClassType IfcFooting::s_type("IfcFooting");
