cmake_minimum_required(VERSION 3.13)

project(Neuton_User_Model
   VERSION 1.0
   LANGUAGES
   C
)

add_library(${PROJECT_NAME}
   neuton_user_model.c
)

add_library(Neuton::UserModel ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
   PRIVATE
       Neuton
)
