template<typename EnumType, typename...T>
class Controller {
	std::tuple<std::vector<T>...> contents;
	ResourceHandler * pRH;
public:
	Controller(ResourceHandler * _pRH) : pRH{pRH} {}
	
	template<EnumType type>
	auto & get() {
		return std::get<static_cast<int>(indx)>(contents);
	}
	
	void update(float, float, const sf::Time & elapsedTime) {
		for (auto & vec : contents) {
			if (!vec.empty()) {
				for (auto it = vec.begin(); it != vec.end();) {
					if (it->getKillFlag()) {
						it = vec.erase(it);
					} else {
						it->update();
						++it;
					}
				}
			}
		}	
	}
	
	void clear() {
		for (auto & vec : contents) {
			vec.clear();
		}
	}
};
