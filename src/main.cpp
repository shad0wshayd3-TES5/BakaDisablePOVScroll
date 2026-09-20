namespace Hooks
{
	namespace hkFirstPersonState
	{
		static void Install()
		{
			static REL::Relocation target{ REL::ID(50730) };
			static constexpr auto  TARGET_ADDR{ 0x45 };
			static constexpr auto  TARGET_RETN{ 0x4E };
			static constexpr auto  TARGET_FILL{ TARGET_RETN - TARGET_ADDR };
			target.write_fill<TARGET_ADDR>(REL::NOP, TARGET_FILL);
		}
	}

	namespace hkThirdPersonState
	{
		static void Install()
		{
			static REL::Relocation target{ REL::ID(50906) };
			static constexpr auto  TARGET_ADDR{ 0x209 };
			static constexpr auto  TARGET_RETN{ 0x22E };
			static constexpr auto  TARGET_FILL{ TARGET_RETN - TARGET_ADDR };
			target.write_fill<TARGET_ADDR>(REL::NOP, TARGET_FILL);
		}
	}

	static void Install()
	{
		hkFirstPersonState::Install();
		hkThirdPersonState::Install();
	}
}

namespace
{
	void MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case SKSE::MessagingInterface::kPostLoad:
			Hooks::Install();
			break;
		default:
			break;
		}
	}
}

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::GetMessagingInterface()->RegisterListener(MessageCallback);
	return true;
}
