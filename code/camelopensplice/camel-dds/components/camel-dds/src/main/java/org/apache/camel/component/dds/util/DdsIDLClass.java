/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.apache.camel.component.dds.util;

public enum DdsIDLClass {

    DATA_READER("DataReader"), DATA_READER_HELPER("DataReaderHelper"),
    DATA_READER_HOLDER("DataReaderHolder"), DATA_READER_IMPL("DataReaderImpl"), DATA_READER_OPS("DataReaderOperations"),
    DATA_WRITER("DataWriter"), DATA_WRITER_HELPER("DataWriterHelper"),
    DATA_WRITER_HOLDER("DataWriterHolder"), DATA_WRITER_IMPL("DataWriterImpl"), DATA_WRITER_OPS("DataWriterOperations"),
    SEQ_HOLDER("SeqHolder"), TYPE_SUPPORT("TypeSupport"), TYPE_SUPPORT_HELPER("TypeSupportHelper"),
    TYPE_SUPPORT_HOLDER("TypeSupportHolder"), TYPE_SUPPORT_OPS("TypeSupportOperations");

    /** Suffix for the generated classes. */
    private String suffix;

    /**
     *
     * @param suffix private constructor with the suffix
     */
    private DdsIDLClass(String suffix) {
        this.suffix = suffix;
    }

    /**
     *
     * @return the suffix associated with the class
     */
    public String getSuffix() {
        return suffix;
    }




}
