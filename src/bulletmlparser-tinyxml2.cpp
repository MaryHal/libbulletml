#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml2.h"
#include "bulletmlerror.h"
#include "bulletmltree.h"

#include <cassert>
#include <cstring>

#include <cstdio>

BulletMLParserTinyXML2::BulletMLParserTinyXML2(const char* filename)
    : curNode_(0)
{
    setName(filename);
}

BulletMLParserTinyXML2::~BulletMLParserTinyXML2() {}

void BulletMLParserTinyXML2::getTree(tinyxml2::XMLNode* node) {
    if (node->ToComment() != 0) return;
    translateNode(node);

    tinyxml2::XMLNode* child;
    for (child = node->FirstChild(); child; child = child->NextSibling()) {
        tinyxml2::XMLText* text;
        if ((text = child->ToText()) != 0) {
            curNode_->setValue(text->Value());
            break;
        }

        getTree(child);
    }

    curNode_ = curNode_->getParent();
}

void BulletMLParserTinyXML2::translateNode(tinyxml2::XMLNode* node) {
    tinyxml2::XMLElement* elem = node->ToElement();
    assert(elem != 0);

    BulletMLNode* xmlNode = addContent(elem->Value());

    if (xmlNode->getName() == BulletMLNode::bulletml) {
        const tinyxml2::XMLAttribute* attr;
        for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
            // If attribute == horizontal
            if (strcmp(attr->Value(), "horizontal") == 0) setHorizontal();
        }
    }
    else {
        MyAttributes mattr;
        const tinyxml2::XMLAttribute* attr;
        for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
            mattr.push_back(attr->Name());
            mattr.push_back(attr->Value());
        }
        addAttribute(mattr, xmlNode);
        if (curNode_ != 0) curNode_->addChild(xmlNode);
    }
    curNode_ = xmlNode;
}

void BulletMLParserTinyXML2::parseImpl(tinyxml2::XMLDocument& doc) {
    if (doc.Error()) {
        throw BulletMLError(std::string(doc.Value()) + ": " + doc.GetErrorStr1());
    }

    tinyxml2::XMLNode* node;
    for (node = doc.FirstChild(); node; node = node->NextSibling()) {
        if (node->ToElement() != 0) {
            getTree(node);
            break;
        }
    }
}

void BulletMLParserTinyXML2::parse() {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(name_);
    parseImpl(doc);
}


