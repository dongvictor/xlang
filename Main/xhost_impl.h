#pragma once
#include "xhost.h"

namespace X
{
	class XHost_Impl :
		public XHost
	{
	public:
		virtual void AddSysCleanupFunc(CLEANUP f) override;
		virtual XRuntime* CreateRuntime() override;
		virtual XRuntime* GetCurrentRuntime() override;
		virtual XStr* CreateStr(const char* data, int size) override;
		virtual bool RegisterPackage(const char* name, APISetBase* pAPISet,PackageCreator creator) override;
		virtual bool RegisterPackage(const char* name, APISetBase* pAPISet,Value& objPackage) override;
		virtual XObj* QueryMember(XRuntime* rt, XObj* pObj, const char* name) override;
		virtual bool QueryPackage(XRuntime* rt, const char* name, Value& objPackage) override;
		virtual XPackage* CreatePackage(APISetBase* pAPISet,void* pRealObj) override;
		virtual XPackage* CreatePackageProxy(XPackage* pPackage, void* pRealObj) override;
		virtual XEvent* CreateXEvent(const char* name) override;
		virtual XFunc* CreateFunction(const char* name, U_FUNC func, X::XObj* pContext = nullptr) override;
		virtual XFunc* CreateFunctionEx(const char* name, U_FUNC_EX func, X::XObj* pContext = nullptr) override;
		virtual XProp* CreateProp(const char* name, U_FUNC setter, U_FUNC getter) override;
		virtual XDict* CreateDict() override;
		virtual XList* CreateList() override;
		virtual XObj* ConvertObjFromPointer(void* pObjectPtr) override;
		virtual std::string StringifyString(const std::string& str) override;
		virtual XBin* CreateBin(char* data, size_t size, bool bOwnData) override;
		virtual X::XLStream* CreateStream(const char* buf=nullptr, long long size=0) override;
		virtual void ReleaseStream(X::XLStream* pStream) override;
		virtual XRemoteObject* CreateRemoteObject(XProxy* proxy) override;
		virtual bool ToBytes(X::Value& input, X::Value& output) override;
		virtual bool FromBytes(X::Value& input, X::Value& output) override;
		virtual bool ConvertToBytes(X::Value& v, X::XLStream* pStream = nullptr) override;
		virtual bool ConvertFromBytes(X::Value& v, X::XLStream* pStream = nullptr) override;
		virtual bool RunCode(std::string& moduleName, std::string& code, X::Value& retVal) override;
		virtual bool RunCodeLine(std::string& codeLine, X::Value& retVal) override;
		virtual bool GetInteractiveCode(std::string& code) override;
		virtual long OnEvent(const char* evtName, EventHandler handler) override;
		virtual void OffEvent(const char* evtName, long Cookie) override;
		virtual Value GetAttr(const X::Value& v, const char* attrName) override;
		virtual void SetAttr(const X::Value& v, const char* attrName, X::Value& attrVal) override;
		virtual AppEventCode HandleAppEvent(int signum) override;
		virtual bool Lrpc_Listen(int port, bool blockMode) override;
		virtual bool Import(XRuntime* rt, const char* moduleName,
			const char* from, const char* thru, X::Value& objPackage) override;
		virtual bool CreateScopeWrapper(XCustomScope* pScope) override;
		virtual bool DeleteScopeWrapper(XCustomScope* pScope) override;
		virtual bool SetExpressionScope(XCustomScope* pScope, X::Value& expr) override;
		virtual bool RunExpression(X::Value& expr, X::Value& result) override;
		virtual bool ExtractNativeObjectFromRemoteObject(X::Value& remoteObj, X::Value& nativeObj) override;
	};
	X::XHost* CreatXHost();
	void DestoryXHost();
}