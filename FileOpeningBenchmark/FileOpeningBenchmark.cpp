#pragma once

#include "catch.hpp"
#include <cstdio>
#include <memory>

// What's faster: reading 10 MB from a single file, or from 500 small files?

// Result:
// It took 10x longer to read from 500 small files 

// Test system:
// HDD: Caviar Green 2 TB 5400 RPM

TEST_CASE( "Opening a large file" )
{
    // Generate test file
    FILE* f = fopen( "largeFile.dat", "w" );

    // Write arbitrary data to file.
    const size_t elementCount = 2'500'000;    
    std::vector<float> buff( elementCount );

    fwrite( buff.data(), sizeof( *buff.data() ), elementCount, f );

    fclose( f );

    SECTION("large file benchmark")
    {
        FILE* f = fopen( "largeFile.dat", "r" );        
        fread( buff.data(), sizeof( *buff.data() ), elementCount, f );
        fclose( f );   
    }
}

TEST_CASE( "Opening several small files") 
{    
    const size_t elementCount = 2'500'000;    
    std::vector<float> buff( elementCount );

    const size_t fileCount = 500;

    std::vector<std::string> fileNames( fileCount );
    for (size_t i = 0; i < fileCount; i++)
    {
        fileNames[i] = "smallFile";
        fileNames[i] += std::to_string(i);
        fileNames[i] += ".dat";
    }

    for (size_t i = 0; i < fileCount; i++)
    {
        FILE* f = fopen( fileNames[i].c_str(), "w" );
        if(f != NULL)
        {
            fwrite( buff.data(), sizeof( *buff.data() ), elementCount / fileCount, f );
            fclose( f );
        }
    }

    SECTION("small file benchmark")
    {
        for (size_t i = 0; i < fileCount; i++)
        {
            FILE* f = fopen( fileNames[i].c_str(), "r" );        
            if (f != NULL)
            {
                fread( buff.data(), sizeof( *buff.data() ), elementCount / fileCount, f );
                fclose( f );
            }
        }
    }
}