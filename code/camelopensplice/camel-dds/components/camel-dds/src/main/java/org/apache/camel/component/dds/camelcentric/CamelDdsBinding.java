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
package org.apache.camel.component.dds.camelcentric;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import javax.activation.DataHandler;
import javax.mail.util.ByteArrayDataSource;

import CamelDDS.CamelAttachment;
import CamelDDS.CamelHeader;
import CamelDDS.CamelMessage;
import CamelDDS.SerializedPOJO;
import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.camel.component.dds.DdsException;

public class CamelDdsBinding {

    public CamelDdsBinding() {

    }

    public Map<String, Object> extractHeadersFromMessage(CamelMessage msg)
        throws DdsException {
        Map<String, Object> headerMap = new HashMap<String, Object>();
        CamelHeader[] hdrs = msg.headers;
        String key = null;
        Object body = null;
        for (CamelHeader hdr : hdrs) {
            key = hdr.name;
            body = getObject(hdr.value.serialized_object);
            headerMap.put(key, body);
        }
        return headerMap;
    }

    public Map<String, DataHandler> extractAttachmentsFromMessage(
            CamelMessage msg) {
        Map<String, DataHandler> attMap = new HashMap<String, DataHandler>();
        CamelAttachment[] atts = msg.attachments;
        String key = null;
        DataHandler handler = null;
        for (CamelAttachment att : atts) {
            key = att.id;
            // Support only File attachments
            byte[] bytes = att.content;
            ByteArrayDataSource s = new ByteArrayDataSource(bytes,
                    att.mime_type);
            handler = new DataHandler(s);
            attMap.put(key, handler);
        }
        return attMap;
    }

    public Object extractBody(CamelMessage msg) throws DdsException {
        Object ret = null;
        SerializedPOJO p = msg.body;
        if (p.serialized_object != null) {
            ret = getObject(p.serialized_object);
        }
        return ret;
    }

    /**
     * 
     * @param exchange
     * @return CamelMessage
     */
    public CamelMessage createCamelMessageFromExchange(String target,
            Exchange exchange) throws Exception {
        CamelMessage msg = new CamelMessage();
        Message m = exchange.getIn();
        msg.message_id = m.getMessageId();
        msg.body = getSerializedObject((Serializable) m.getBody());
        if (target != null) {
            msg.target = target;
        } else {
            target = "";
        }

        Map<String, Object> headers = m.getHeaders();
        Iterator<String> itr = headers.keySet().iterator();
        CamelHeader[] hdrs = new CamelHeader[headers.size()];
        int x = 0;
        String key = null;
        while (itr.hasNext()) {
            key = itr.next();
            hdrs[x++] = getCamelHeader(key, headers.get(key));
        }

        Map<String, DataHandler> atts = m.getAttachments();
        itr = atts.keySet().iterator();
        CamelAttachment[] ats = new CamelAttachment[atts.size()];
        x = 0;
        while (itr.hasNext()) {
            key = itr.next();
            ats[x++] = getCamelAttachment(key, atts.get(key));
        }
        msg.attachments = ats;
        msg.headers = hdrs;
        return msg;
    }

    private CamelAttachment getCamelAttachment(String key, DataHandler handler)
        throws DdsException {
        try {
            InputStream is = handler.getInputStream();
            long length = is.available();
            byte[] bytes = new byte[(int) length];
            is.read(bytes);
            String mimetype = handler.getContentType();
            return new CamelAttachment(key, mimetype, bytes);
        } catch (IOException e) {
            throw new DdsException(e);
        }
    }

    private CamelHeader getCamelHeader(String key, Object obj)
        throws DdsException {
        SerializedPOJO serializedHeader = getSerializedObject((Serializable) obj);
        return new CamelHeader(key, serializedHeader);
    }

    private SerializedPOJO getSerializedObject(Serializable object)
        throws DdsException {
        String className = object.getClass().getName();
        byte[] byteArray = getBytes(object);
        return new SerializedPOJO(className, byteArray);
    }

    private byte[] getBytes(Serializable obj) throws DdsException {
        byte[] data = null;
        try {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(bos);
            oos.writeObject(obj);
            oos.flush();
            oos.close();
            bos.close();
            data = bos.toByteArray();
        } catch (IOException e) {
            throw new DdsException(e);
        }
        return data;
    }

    private Object getObject(byte[] buf) throws DdsException {
        Object ret = null;
        try {
            ByteArrayInputStream b = new ByteArrayInputStream(buf);
            ObjectInputStream ostr = new ObjectInputStream(b);
            ret = ostr.readObject();
            ostr.close();
            b.close();
        } catch (IOException e) {
            throw new DdsException(e);
        } catch (ClassNotFoundException e) {
            throw new DdsException(e);
        }
        return ret;
    }
}
