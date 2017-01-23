/*
 *  Query.cpp
 *  
 *
 *  Created by Eugene Kin Chee Yip on 6/01/11.
 *  Copyright 2011 Potential Publishers. All rights reserved.
 *
 */

#include "Query.hpp"

#include "../ast/Node.hpp"

namespace tools {

	// Retrieve children recursively.
	std::vector<forec::ast::Node *> Query::retrieveAll(forec::ast::Node &source, const std::string &type, const std::string &variant) {
		std::vector<forec::ast::Node *> results = source.findAll(type, variant);
		return results;
	}
	
	std::vector<forec::ast::Node *> Query::retrieveAll(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant) {
		std::vector<forec::ast::Node *> results;
		for (std::vector<forec::ast::Node *>::iterator i = source.begin(); i != source.end(); ++i) {\
			std::vector<forec::ast::Node *> subResults = Query::retrieveAll(*(*i), type, variant);
			results.insert(results.end(), subResults.begin(), subResults.end());
		}
		return results;
	}

	// Retrieve children.
	std::vector<forec::ast::Node *> Query::retrieveChildren(forec::ast::Node &source, const std::string &type, const std::string &variant) {
		std::vector<forec::ast::Node *> results = source.find(type, variant);
		return results;
	}
	
	std::vector<forec::ast::Node *> Query::retrieveChildren(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant) {
		std::vector<forec::ast::Node *> results;
		for (std::vector<forec::ast::Node *>::iterator i = source.begin(); i != source.end(); ++i) {
			std::vector<forec::ast::Node *> subResults = Query::retrieveChildren(*(*i), type, variant);
			results.insert(results.end(), subResults.begin(), subResults.end());
		}
		return results;
	}

	std::vector<forec::ast::Node *> Query::filterIn(forec::ast::Node &source, const std::string &type, const std::string &variant) {
		return filter(source, type, variant, true);
	}
	
	std::vector<forec::ast::Node *> Query::filterIn(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant) {
		return filter(source, type, variant, true);
	}

	std::vector<forec::ast::Node *> Query::filterOut(forec::ast::Node &source, const std::string &type, const std::string &variant) {
		return filter(source, type, variant, false);
	}
	
	std::vector<forec::ast::Node *> Query::filterOut(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant) {
		return filter(source, type, variant, false);
	}

	// Filter children recursively based on type and variant.
	std::vector<forec::ast::Node *> Query::filter(forec::ast::Node &source, const std::string &type, const std::string &variant, const bool condition) {
		std::vector<forec::ast::Node *> results;
		if (source.has(type, variant) == condition) {
			results.push_back(&source);
		}
		return results;
	}

	std::vector<forec::ast::Node *> Query::filter(std::vector<forec::ast::Node *> &source, const std::string &type, const std::string &variant, const bool condition) {
		std::vector<forec::ast::Node *> results;
		for (std::vector<forec::ast::Node *>::iterator i = source.begin(); i != source.end(); ++i) {
			std::vector<forec::ast::Node *> subResults = Query::filter(*(*i), type, variant, condition);
			results.insert(results.end(), subResults.begin(), subResults.end());
		}
		return results;
	}
}
