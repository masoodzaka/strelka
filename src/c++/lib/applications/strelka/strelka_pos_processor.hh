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

///
/// note coding convention for all ranges '_pos fields' is:
/// XXX_begin_pos is zero-indexed position at the beginning of the range
/// XXX_end_pos is zero-index position 1 step after the end of the range
///

#pragma once


#include "CallableProcessor.hh"
#include "NoiseBuffer.hh"
#include "strelka_shared.hh"
#include "SomaticIndelVcfWriter.hh"
#include "strelka_sample_type.hh"
#include "strelka_streams.hh"

#include "starling_common/starling_pos_processor_base.hh"


///
///
struct strelka_pos_processor : public starling_pos_processor_base
{
    typedef starling_pos_processor_base base_t;

    strelka_pos_processor(
        const strelka_options& opt,
        const strelka_deriv_options& dopt,
        const reference_contig_segment& ref,
        const strelka_streams& client_io);


    void
    insert_noise_pos(
        const pos_t pos,
        const SiteNoise& sn);

private:

    void
    process_pos_variants(const pos_t pos) override;

    void
    process_pos_snp_somatic(const pos_t pos);

    void
    process_pos_indel_somatic(const pos_t pos);

    void
    post_align_clear_pos(const pos_t pos) override
    {
        _noisePos.clear_pos(pos);
    }

    void
    run_post_call_step(
        const int stage_no,
        const pos_t pos) override;

    void
    write_counts(const pos_range& output_report_range) const override;

    bool
    derived_empty() const override
    {
        return _indelWriter.empty();
    }

    /////////////////////////////

    // keep some of the original strelka classes handy so we don't
    // have to down-cast:
    const strelka_options& _opt;
    const strelka_deriv_options& _dopt;
    const strelka_streams& _client_io;

    extra_position_data _tier2_epd[MAX_SAMPLE];

    CallableProcessor _callProcessor;

    // enables delayed indel write:
    SomaticIndelVcfWriter _indelWriter;

    unsigned _indelRegionIndexNormal;
    unsigned _indelRegionIndexTumor;

    NoiseBuffer _noisePos;
};
