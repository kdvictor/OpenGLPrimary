#pragma once

unsigned char* LoadFileContent(const char* const& pFilePath);

unsigned char* DecodeBMP(unsigned char* const& pFileContent, int& width, int& height);