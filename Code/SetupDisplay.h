#pragma once

#include "IncludeGraphics.h"

#define DG_NAME_UNKNWN "Unknown"
#define DG_NAME_OPENGL "OpenGL"

struct BaseDisplayContext {
	unsigned short sw_Width;
	unsigned short sw_Height;

	BaseDisplayContext() {
		sw_Width = 1024;
		sw_Height = 600;
	}
};


struct TypeDisplayDriver {
	bool rq_UpdateDisplayDriver;

	unsigned short v_Minor;
	unsigned short v_Major;

	const char* d_Name;

public:
	enum GetterVersions {
		GET_MINOR_VERSION,
		GET_MAJOR_VERSION,
	};

	TypeDisplayDriver() {
		rq_UpdateDisplayDriver = false;

		v_Minor = 0;
		v_Major = 0;

		d_Name = DG_NAME_UNKNWN;
	}

	void setVersions(unsigned short minor, unsigned short major) {
		v_Minor = minor;
		v_Major = major;
		rq_UpdateDisplayDriver = true;
	}

	unsigned short getVersion(GetterVersions version) const {
		switch (version) {
			case GET_MINOR_VERSION:
				return v_Minor;
			
			case GET_MAJOR_VERSION:
				return v_Major;
		};

		return 0;
	}

	const char* getDriverName() const {
		return d_Name;
	}
};

struct OpenGLDisplayDriver : TypeDisplayDriver {
	OpenGLDisplayDriver() {
		v_Minor = 3;
		v_Major = 0;

		d_Name = DG_NAME_OPENGL;
	}
};

class SetupDisplay
{

public:
	enum CodeDestroyReasons {
		NORMAL_REASON,
		DISPLAY_ERROR_REASON,
		DRIVER_ERROR_REASON,
	};

	SetupDisplay						();

	void InitDisplay					(BaseDisplayContext& bDisplayContext);
	void InitGraphics					(TypeDisplayDriver& tDisplayDriver);
	
	void UpdateDisplay					(BaseDisplayContext& bDisplayContext);
	void UpdateGraphics					(TypeDisplayDriver& tDisplayDriver);

	void DestroyGraphics				(TypeDisplayDriver& tDisplayDriver);
	void DestroyDisplay					(BaseDisplayContext& bDisplayContext);

	bool RequestedDestroySetup			() const;

	CodeDestroyReasons GetDestroyReason	() const;

	template	<typename T>

	static T& GetDisplayDriver			(TypeDisplayDriver& tDisplayDriver);

private:
	bool rq_DestroySetup;

	CodeDestroyReasons rs_DestroySetup;
};

template<typename T>
inline T& SetupDisplay::GetDisplayDriver(TypeDisplayDriver& tDisplayDriver)
{
	return static_cast<T&>(tDisplayDriver);
}
