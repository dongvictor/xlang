#pragma once
#include "exp.h"
#include "object.h"
#include "stackframe.h"

namespace X 
{ 
namespace AST
{
class ScopeProxy :
	public Scope
{
	// Inherited via Scope
	virtual AST::ScopeWaitingStatus IsWaitForCall() override
	{
		return AST::ScopeWaitingStatus::HasWaiting;
	}
	virtual Scope* GetParentScope() override;
public:
	ScopeProxy() :
		Scope()
	{
	}
};
class AsOp :
	virtual public BinaryOp
{
public:
	AsOp(short op) :
		Operator(op),
		BinaryOp(op)
	{
		m_type = ObType::As;
	}
};
class From :
	virtual public UnaryOp
{
	std::string m_path;
public:
	From(short op) :
		Operator(op),
		UnaryOp(op)
	{
		m_type = ObType::From;
	}
	std::string GetPath()
	{
		return m_path;
	}
	std::string CalcPath(Expression* l, Expression* r)
	{
		std::string l_name;
		std::string r_name;
		if (l)
		{
			if (l->m_type == ObType::Var)
			{
				l_name = (dynamic_cast<Var*>(l))->GetNameString();
			}
			else if (l->m_type == ObType::BinaryOp)
			{
				l_name = CalcPath((dynamic_cast<BinaryOp*>(l))->GetL(),
					(dynamic_cast<BinaryOp*>(l))->GetR());
			}
		}
		if (r)
		{
			if (r->m_type == ObType::Var)
			{
				r_name = (dynamic_cast<Var*>(r))->GetNameString();
			}
			else if (r->m_type == ObType::BinaryOp)
			{
				r_name = CalcPath((dynamic_cast<BinaryOp*>(r))->GetL(),
					(dynamic_cast<BinaryOp*>(r))->GetR());
			}
		}
		return l_name + "/" + r_name;
	}
	virtual void ScopeLayout() override
	{
		UnaryOp::ScopeLayout();
		//Calc Path
		//format like folder1/folder2/.../folderN
		if (R)
		{
			if (R->m_type == ObType::Var)
			{
				m_path = (dynamic_cast<Var*>(R))->GetNameString();
			}
			else if (R->m_type == ObType::BinaryOp)
			{
				m_path = CalcPath((dynamic_cast<BinaryOp*>(R))->GetL(),
					(dynamic_cast<BinaryOp*>(R))->GetR());
			}
		}
	}
	virtual bool Run(Runtime* rt, XObj* pContext,
		Value& v, LValue* lValue = nullptr) override;
};

enum class ImportType
{
	Builtin,
	XModule,
	PyModule,
};

struct ImportInfo
{
	ImportType type = ImportType::Builtin;
	std::string name;
	std::string alias;
	std::string fileName;
};
class Import :
	virtual public BinaryOp
{
	//from path import moudule_lists
	//only put one path after term: from
	std::string m_path;

	std::vector<ImportInfo> m_importInfos;
	bool FindAndLoadExtensions(Runtime* rt,
		std::string& curModulePath, std::string& loadingModuleName);
	bool FindAndLoadXModule(Runtime* rt,
		std::string& curModulePath, std::string& loadingModuleName,
		Module** ppSubModule);
public:
	Import(short op) :
		Operator(op),
		BinaryOp(op)
	{
		m_type = ObType::Import;
	}
	virtual bool OpWithOperands(
		std::stack<AST::Expression*>& operands)
	{
		auto operandR = operands.top();
		operands.pop();
		SetR(operandR);
		if (!operands.empty())
		{//from can be igored
			auto operandL = operands.top();
			operands.pop();
			SetL(operandL);
		}
		operands.push(this);
		return true;
	}
	std::string ConvertDotSeqToString(Expression* expr);
	virtual void ScopeLayout() override;
	virtual bool Run(Runtime* rt, XObj* pContext,
		Value& v, LValue* lValue = nullptr) override;
	virtual bool CalcCallables(Runtime* rt, XObj* pContext,
		std::vector<Scope*>& callables) override;
};
}
}