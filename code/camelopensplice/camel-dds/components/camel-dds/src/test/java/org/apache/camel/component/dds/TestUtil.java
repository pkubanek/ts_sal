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

package org.apache.camel.component.dds;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;

public class TestUtil {

    public static Object getDDSMessage() throws Exception {
        Class[] args = new Class[] {int.class, String.class};
        Object[] objArgs = new Object[] {new Integer(0), "Chat Message"};
        Class c = Class.forName("Chat.ChatMessage");
        Constructor ctr = c.getConstructor(args);
        Object obj = ctr.newInstance(objArgs);
        return obj;
    }

    public static Object getDDSMessage(int id, String msg) throws Exception {
        Class[] args = new Class[] {int.class, String.class};
        Object[] objArgs = new Object[] {new Integer(id), msg};
        Class c = Class.forName("Chat.ChatMessage");
        Constructor ctr = c.getConstructor(args);
        Object obj = ctr.newInstance(objArgs);
        return obj;
    }

    public static int getId(Object message) throws Exception {
        int ret = -1;
        Class c = Class.forName("Chat.ChatMessage");
        Field f = c.getDeclaredField("userID");
        ret = f.getInt(message);
        return ret;
    }

    public static String getMessage(Object message) throws Exception {
        String ret = null;
        Class c = Class.forName("Chat.ChatMessage");
        Field f = c.getDeclaredField("message");
        ret = (String)f.get(message);
        return ret;
    }

}
