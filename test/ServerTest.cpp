//
// Created by Vlad-Andrei Loghin on 04.07.23.
//

#include <gtest/gtest.h>

#include "../src/Server/pch.h"
#include "../src/Server/serverMain.h"

TEST(ServerTest, Init) {
  Server s(8099);
  s.Init();
  ASSERT_STRNE(s.GetLocaltime(), "empty");
}
