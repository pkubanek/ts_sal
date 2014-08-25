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

import junit.framework.TestCase;

public class DdsIDLClassesTest extends TestCase {

    public void testDDSReflect() {
        DDSReflect reflect = new DDSReflect("Chat.ChatMessage");
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_READER).getName().equals("Chat.ChatMessageDataReader"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_READER_HELPER).getName().equals("Chat.ChatMessageDataReaderHelper"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_READER_HOLDER).getName().equals("Chat.ChatMessageDataReaderHolder"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_READER_IMPL).getName().equals("Chat.ChatMessageDataReaderImpl"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_READER_OPS).getName().equals("Chat.ChatMessageDataReaderOperations"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_WRITER).getName().equals("Chat.ChatMessageDataWriter"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_WRITER_HOLDER).getName().equals("Chat.ChatMessageDataWriterHolder"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_WRITER_IMPL).getName().equals("Chat.ChatMessageDataWriterImpl"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.DATA_WRITER_OPS).getName().equals("Chat.ChatMessageDataWriterOperations"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.SEQ_HOLDER).getName().equals("Chat.ChatMessageSeqHolder"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.TYPE_SUPPORT_HELPER).getName().equals("Chat.ChatMessageTypeSupportHelper"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.TYPE_SUPPORT).getName().equals("Chat.ChatMessageTypeSupport"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.TYPE_SUPPORT_HOLDER).getName().equals("Chat.ChatMessageTypeSupportHolder"));
        assertTrue(reflect.getDDSClass(DdsIDLClass.TYPE_SUPPORT_OPS).getName().equals("Chat.ChatMessageTypeSupportOperations"));
    }
}
