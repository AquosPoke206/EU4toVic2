#include "V2FactoryInvention.h"
#include "V2FactoryInventionEffect.h"
#include "ParserHelpers.h"


mappers::V2FactoryInvention::V2FactoryInvention(std::istream& theStream)
{
	// we need ���� for jean_jaur�s, johann_heinrich_von_th�nen, l�on_walras, eugen_von_b�hm_bawerk :/
	registerKeyword(std::regex("[����a-z_]+"), [this](const std::string& invention, std::istream& theStream)
		{
			V2FactoryInventionEffect theEffect(theStream);
			if (!theEffect.getFactoryName().empty())
			{
				factoryInventionMap.insert(std::make_pair(theEffect.getFactoryName(), invention));
			}
		});
	registerKeyword(std::regex("[a-zA-Z0-9\\_.:]+"), commonItems::ignoreItem);

	parseStream(theStream);
}
