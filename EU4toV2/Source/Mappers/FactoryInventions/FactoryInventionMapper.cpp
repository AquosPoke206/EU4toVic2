#include "FactoryInventionMapper.h"
#include "FactoryInventionEffect.h"
#include "ParserHelpers.h"
#include "OSCompatibilityLayer.h"
#include "../../Configuration.h"
#include "Log.h"
#include <set>

mappers::FactoryInventionMapper::FactoryInventionMapper()
{
	LOG(LogLevel::Info) << "\tLoading V2 Factory Inventions";
	registerKeys();
	std::set<std::string> filenames;
	Utils::GetAllFilesInFolder(theConfiguration.getVic2Path() + "/inventions/", filenames);
	for (const auto& filename : filenames)
	{
		parseFile(theConfiguration.getVic2Path() + "/inventions/" + filename);
	}
	clearRegisteredKeywords();
}

mappers::FactoryInventionMapper::FactoryInventionMapper(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::FactoryInventionMapper::registerKeys()
{
	// we need ���� for jean_jaur�s, johann_heinrich_von_th�nen, l�on_walras, eugen_von_b�hm_bawerk :/
	registerRegex("[����a-z_]+", [this](const std::string& invention, std::istream& theStream)
		{
			FactoryInventionEffect theEffect(theStream);
			if (!theEffect.getFactoryName().empty())
			{
				factoryInventionMap.insert(std::make_pair(theEffect.getFactoryName(), invention));
			}
		});
	registerRegex("[a-zA-Z0-9\\_.:]+", commonItems::ignoreItem);
}
