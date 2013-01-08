/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_UTIL_FUNCTIONS_H
#define __LIBCASSANDRA_UTIL_FUNCTIONS_H

#include <string>

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/column_family_definition.h"
#include "libcassandra/indexed_slices_query.h"
#include "libcassandra/keyspace_definition.h"


namespace libcassandra
{


/**
 * @param[in] url to parse
 * @return the port number from the given url
 */
int parsePortFromURL(const std::string &url);


/**
 * @param[in] url to parse
 * @return the host namefrom the given url
 */
std::string parseHostFromURL(const std::string &url);

/**
 * Convert a ColumnDefinition object to the thrift 
 * equivalent - ColumnDef
 * @param[in] col_def a ColumnDefinition object
 * @return a thrift ColumnDef object equivalent to the col_def input
 */
org::apache::cassandra::ColumnDef createColumnDefObject(const ColumnDefinition& col_def);

/**
 * Convert a KeyspaceDefinition object to the thrift 
 * equivalent - KsDef
 * @param[in] ks_def a KeyspaceDefinition object
 * @return a thrift KsDef object equivalent to the ks_def input
 */
org::apache::cassandra::KsDef createKsDefObject(const KeyspaceDefinition& ks_def);

/**
 * Convert a ColumnFamilyDefinition object to the thrift 
 * equivalent - CfDef
 * @param[in] cf_def a ColumnFamilyDefinition object
 * @return a thrift CfDef object equivalent to the cf_def input
 */
org::apache::cassandra::CfDef createCfDefObject(const ColumnFamilyDefinition& ks_def);

/**
 * Convert a IndexedSlicesQuery object to the thrift 
 * equivalent - SlicePredicate
 * @param[in] query an IndexedSlicesQuery object
 * @return a thrift SlicePredicate object equivalent to the query input
 */
org::apache::cassandra::SlicePredicate createSlicePredicateObject(const IndexedSlicesQuery& query);

/**
 * Extract the columns from the vector of columns or super columns
 * @param[in] cols vector to process
 * @return vector of Column objects
 */
std::vector<org::apache::cassandra::Column>
getColumnList(std::vector<org::apache::cassandra::ColumnOrSuperColumn>& cols);

/**
 * Extract the super columns from the vector of columns or super columns
 * @param[in] cols vector to process
 * @return vector of SuperColumn objects
 */
std::vector<org::apache::cassandra::SuperColumn>
getSuperColumnList(std::vector<org::apache::cassandra::ColumnOrSuperColumn>& cols);

/**
 * @return a timestamp in micro-seconds
 */
int64_t createTimestamp();

/**
 * Convert given 64 bit integer to big-endian
 * format and place these raw bytes in a std::string
 * This is the format thrift expects for a LongType
 * @param[in] t integer to work with
 * @return a std::string representing the input in big-endian format
 */
std::string serializeLong(int64_t t);

/**
 * Convert given string in big-endian format
 * to a 64 bit integer
 * @param[in] t string to work with
 * @return a int64_t 
 */
int64_t deserializeLong(std::string& t);

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_UTIL_FUNCTIONS_H */
