install(
    TARGETS tb64
    RUNTIME COMPONENT tb64_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
