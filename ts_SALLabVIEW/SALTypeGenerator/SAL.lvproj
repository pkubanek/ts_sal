<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Element" Type="Folder">
			<Item Name="Element.lvclass" Type="LVClass" URL="../Element/Element.lvclass"/>
		</Item>
		<Item Name="ElementFactory" Type="Folder">
			<Item Name="ElementFactory.lvclass" Type="LVClass" URL="../ElementFactory/ElementFactory/ElementFactory.lvclass"/>
			<Item Name="IElementFactory.lvclass" Type="LVClass" URL="../ElementFactory/IElementFactory/IElementFactory.lvclass"/>
		</Item>
		<Item Name="Elements" Type="Folder">
			<Item Name="Primitives" Type="Folder">
				<Item Name="Numerics" Type="Folder">
					<Item Name="FloatingPoints" Type="Folder">
						<Item Name="Double.lvclass" Type="LVClass" URL="../Elements/Double/Double.lvclass"/>
						<Item Name="Float.lvclass" Type="LVClass" URL="../Elements/Float/Float.lvclass"/>
					</Item>
					<Item Name="Integers" Type="Folder">
						<Item Name="Signed" Type="Folder">
							<Item Name="Long.lvclass" Type="LVClass" URL="../Elements/Long/Long.lvclass"/>
							<Item Name="LongLong.lvclass" Type="LVClass" URL="../Elements/LongLong/LongLong.lvclass"/>
							<Item Name="Short.lvclass" Type="LVClass" URL="../Elements/Short/Short.lvclass"/>
						</Item>
						<Item Name="Unsigned" Type="Folder">
							<Item Name="Char.lvclass" Type="LVClass" URL="../Elements/Char/Char.lvclass"/>
							<Item Name="UnsignedLong.lvclass" Type="LVClass" URL="../Elements/UnsignedLong/UnsignedLong.lvclass"/>
							<Item Name="UnsignedLongLong.lvclass" Type="LVClass" URL="../Elements/UnsignedLongLong/UnsignedLongLong.lvclass"/>
							<Item Name="UnsignedShort.lvclass" Type="LVClass" URL="../Elements/UnsignedShort/UnsignedShort.lvclass"/>
						</Item>
						<Item Name="Signed.lvclass" Type="LVClass" URL="../Elements/Signed/Signed.lvclass"/>
						<Item Name="Unsigned.lvclass" Type="LVClass" URL="../Elements/Unsigned/Unsigned.lvclass"/>
					</Item>
					<Item Name="FloatingPoint.lvclass" Type="LVClass" URL="../Elements/FloatingPoint/FloatingPoint.lvclass"/>
					<Item Name="Integer.lvclass" Type="LVClass" URL="../Elements/Integer/Integer.lvclass"/>
				</Item>
				<Item Name="Boolean.lvclass" Type="LVClass" URL="../Elements/Boolean/Boolean.lvclass"/>
				<Item Name="Numeric.lvclass" Type="LVClass" URL="../Elements/Numeric/Numeric.lvclass"/>
				<Item Name="String.lvclass" Type="LVClass" URL="../Elements/String/String.lvclass"/>
			</Item>
			<Item Name="Array.lvclass" Type="LVClass" URL="../Elements/Array/Array.lvclass"/>
			<Item Name="Primitive.lvclass" Type="LVClass" URL="../Elements/Primitive/Primitive.lvclass"/>
		</Item>
		<Item Name="FileSelector" Type="Folder">
			<Item Name="FileSelector.lvclass" Type="LVClass" URL="../FileSelector/FileSelector.lvclass"/>
		</Item>
		<Item Name="IDLFile" Type="Folder">
			<Item Name="IDLFile.lvclass" Type="LVClass" URL="../IDLFile/IDLFile.lvclass"/>
		</Item>
		<Item Name="InterfaceTypes" Type="Folder">
			<Item Name="Cold_current.ctl" Type="VI" URL="../InterfaceTypes/Cold_current.ctl"/>
		</Item>
		<Item Name="Module" Type="Folder">
			<Item Name="Module.lvclass" Type="LVClass" URL="../Module/Module.lvclass"/>
		</Item>
		<Item Name="Topic" Type="Folder">
			<Item Name="Topic.lvclass" Type="LVClass" URL="../Topic/Topic.lvclass"/>
		</Item>
		<Item Name="TypeConstructor" Type="Folder">
			<Item Name="TypeConstructor.lvclass" Type="LVClass" URL="../TypeConstructor/TypeConstructor.lvclass"/>
		</Item>
		<Item Name="Typedefs" Type="Folder">
			<Item Name="ClusterInfo.ctl" Type="VI" URL="../Typedefs/ClusterInfo.ctl"/>
			<Item Name="CollectionInfo.ctl" Type="VI" URL="../Typedefs/CollectionInfo.ctl"/>
			<Item Name="ControlInfo.ctl" Type="VI" URL="../Typedefs/ControlInfo.ctl"/>
			<Item Name="ElementType.ctl" Type="VI" URL="../Typedefs/ElementType.ctl"/>
			<Item Name="LibraryInfo.ctl" Type="VI" URL="../Typedefs/LibraryInfo.ctl"/>
		</Item>
		<Item Name="salMain.vi" Type="VI" URL="../salMain.vi"/>
		<Item Name="salMain2.vi" Type="VI" URL="../salMain2.vi"/>
		<Item Name="writeColdCurrent.vi" Type="VI" URL="../InterfaceTypes/writeColdCurrent.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVNumericRepresentation.ctl" Type="VI" URL="/&lt;vilib&gt;/numeric/LVNumericRepresentation.ctl"/>
				<Item Name="LVPointTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVPointTypeDef.ctl"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
