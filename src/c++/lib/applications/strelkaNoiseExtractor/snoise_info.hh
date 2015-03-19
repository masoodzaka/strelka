// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Starka
// Copyright (c) 2009-2014 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/sequencing/licenses/>
//

///
/// \author Chris Saunders
///

#pragma once

#include "blt_util/prog_info.hh"
#include "starling_common/version.hh"


struct snoise_info : public prog_info
{
    static
    const prog_info& get()
    {
        static const snoise_info vci;
        return vci;
    }

private:
    const char* name() const
    {
        static const char NAME[] = "StrelkaNoiseExtractor";
        return NAME;
    }

    const char* version() const
    {
        return starka::getFullVersion();
    }

    void usage(const char* xmessage = nullptr) const;

    void doc() const {}

    snoise_info() {}
    virtual ~snoise_info() {}
};