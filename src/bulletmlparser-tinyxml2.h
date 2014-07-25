/// BulletML のパーサ・ツリー by tinyxml
/**
 * tinyxmlによるBulletMLのパーサ
 */

#ifndef _bulletmlparser_tinyxml2_h_
#define _bulletmlparser_tinyxml2_h_

#include <string>

#include "bulletmlparser.h"
#include "bulletmlcommon.h"

#include "tinyxml2/tinyxml2.h"

class BulletMLNode;

class BulletMLParserTinyXML2 : public BulletMLParser {
public:
    DECLSPEC BulletMLParserTinyXML2(const char* filename);
    DECLSPEC virtual ~BulletMLParserTinyXML2();

    DECLSPEC virtual void parse();
    DECLSPEC virtual void parseImpl(tinyxml2::XMLDocument& doc);

protected:
    void getTree(tinyxml2::XMLNode* node);
    void translateNode(tinyxml2::XMLNode* node);

private:
    BulletMLNode* curNode_;
};

#endif // _bulletmlparser_tinyxml2_h_

