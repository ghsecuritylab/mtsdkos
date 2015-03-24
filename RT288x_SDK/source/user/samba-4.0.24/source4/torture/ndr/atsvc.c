/* 
   Unix SMB/CIFS implementation.
   test suite for atsvc ndr operations

   Copyright (C) Jelmer Vernooij 2007
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"
#include "torture/ndr/ndr.h"
#include "librpc/gen_ndr/ndr_atsvc.h"
#include "torture/ndr/proto.h"

static const uint8_t jobenum_in_data[] = {
  0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x32, 0x00,
  0x4b, 0x00, 0x44, 0x00, 0x43, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static bool jobenum_in_check(struct torture_context *tctx, 
							 struct atsvc_JobEnum *r)
{
	torture_assert(tctx, r->in.servername != NULL, "servername ptr");
	torture_assert_str_equal(tctx, r->in.servername, "WIN2KDC1", "servername");
	torture_assert_int_equal(tctx, r->in.ctr->entries_read, 0, "ctr entries read");
	torture_assert(tctx, r->in.ctr->first_entry == NULL, "ctr entries first_entry");
	torture_assert_int_equal(tctx, r->in.preferred_max_len, -1, "preferred max len");
	torture_assert(tctx, r->in.resume_handle != NULL, "resume handle ptr");
	torture_assert_int_equal(tctx, *r->in.resume_handle, 0, "resume handle");
	return true;
}

static const uint8_t jobenum_out_data[] = {
  0x07, 0x00, 0x00, 0x00, 0x28, 0x14, 0x0a, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x13, 0x00, 0x00, 0x40, 0x18, 0x0a, 0x00, 0x02, 0x00, 0x00, 0x00,
  0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00, 0x02, 0x13, 0x00, 0x00,
  0x30, 0x18, 0x0a, 0x00, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xe4, 0x0a, 0x05,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x13, 0x00, 0x00, 0x20, 0x18, 0x0a, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x13, 0x00, 0x00, 0x10, 0x18, 0x0a, 0x00, 0x05, 0x00, 0x00, 0x00,
  0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00, 0x02, 0x13, 0x00, 0x00,
  0x00, 0x18, 0x0a, 0x00, 0x06, 0x00, 0x00, 0x00, 0xc0, 0xe4, 0x0a, 0x05,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x13, 0x00, 0x00, 0xf0, 0x17, 0x0a, 0x00,
  0x07, 0x00, 0x00, 0x00, 0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x13, 0x00, 0x00, 0xe0, 0x17, 0x0a, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00,
  0x6f, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x62, 0x00, 0x61, 0x00, 0x72, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00,
  0x65, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x2e, 0x00,
  0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00,
  0x6f, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x66, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00,
  0x65, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x2e, 0x00,
  0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00,
  0x6f, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0xac, 0x34, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

static bool jobenum_out_check(struct torture_context *tctx, 
							 struct atsvc_JobEnum *r)
{
	torture_assert_int_equal(tctx, r->out.ctr->entries_read, 7, "entries read");
	torture_assert(tctx, r->out.ctr->first_entry != NULL, "first entry");
	torture_assert_int_equal(tctx, r->out.ctr->first_entry[0].job_id, 1, "job id");
	torture_assert_int_equal(tctx, r->out.ctr->first_entry[0].job_time, 84600000, "job time");
	torture_assert_int_equal(tctx, r->out.ctr->first_entry[0].days_of_week, 0x2, "days of week");
	torture_assert_int_equal(tctx, r->out.ctr->first_entry[0].flags, 0x13, "flags");
	torture_assert_str_equal(tctx, r->out.ctr->first_entry[0].command, "foo.exe", "command");
	torture_assert(tctx, r->out.total_entries != NULL, "total entries ptr");
	torture_assert_int_equal(tctx, *r->out.total_entries, 7, "total entries");
	torture_assert(tctx, r->out.resume_handle, "resume handle ptr");
	torture_assert_int_equal(tctx, *r->out.resume_handle, 0, "resume handle");
	torture_assert_ntstatus_ok(tctx, r->out.result, "return code");

	return true;
}

static const uint8_t jobadd_in_data[] = {
  0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x32, 0x00,
  0x4b, 0x00, 0x44, 0x00, 0x43, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x2e, 0x00,
  0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00
};

static bool jobadd_in_check(struct torture_context *tctx, 
							 struct atsvc_JobAdd *r)
{
	torture_assert_str_equal(tctx, r->in.servername, "WIN2KDC1", "servername");
	torture_assert_int_equal(tctx, r->in.job_info->job_time, 84600000, "time");
	torture_assert_int_equal(tctx, r->in.job_info->days_of_month, 0, "days of month");
	torture_assert_int_equal(tctx, r->in.job_info->days_of_week, 0x2, "days of week");
	torture_assert_int_equal(tctx, r->in.job_info->flags, 17, "flags");
	torture_assert_str_equal(tctx, r->in.job_info->command, "foo.exe", "command");

	return true;
}

static const uint8_t jobadd_out_data[] = {
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static bool jobadd_out_check(struct torture_context *tctx, 
							 struct atsvc_JobAdd *r)
{
	torture_assert_int_equal(tctx, *r->out.job_id, 14, "job id");
	torture_assert_ntstatus_ok(tctx, r->out.result, "return code");
	return true;
}

static const uint8_t jobdel_in_data[] = {
  0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x32, 0x00,
  0x4b, 0x00, 0x44, 0x00, 0x43, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00
};

static bool jobdel_in_check(struct torture_context *tctx, 
							 struct atsvc_JobDel *r)
{
	torture_assert_str_equal(tctx, r->in.servername, "WIN2KDC1", "servername");
	torture_assert_int_equal(tctx, r->in.min_job_id, 14, "min job id");
	torture_assert_int_equal(tctx, r->in.max_job_id, 14, "max job id");
	return true;
}

static const uint8_t jobdel_out_data[] = {
  0xde, 0x0e, 0x00, 0x00
};

static bool jobdel_out_check(struct torture_context *tctx, 
							 struct atsvc_JobDel *r)
{
	/* FIXME: Check for unknown code 0x00000ede */
	return true;
}

static const uint8_t jobgetinfo_in_data[] = {
  0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x32, 0x00,
  0x4b, 0x00, 0x44, 0x00, 0x43, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00
};

static bool jobgetinfo_in_check(struct torture_context *tctx, 
								struct atsvc_JobGetInfo *r)
{
	torture_assert_str_equal(tctx, r->in.servername, "WIN2KDC1", "servername");
	torture_assert_int_equal(tctx, r->in.job_id, 1, "job id");
	return true;
}

static const uint8_t jobgetinfo_out_data[] = {
  0x88, 0xe2, 0x09, 0x00, 0xc0, 0xe4, 0x0a, 0x05, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x13, 0x09, 0x00, 0x98, 0xe2, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x66, 0x00, 0x6f, 0x00,
  0x6f, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

static bool jobgetinfo_out_check(struct torture_context *tctx, 
								struct atsvc_JobGetInfo *r)
{
	torture_assert(tctx, *r->out.job_info != NULL, "job info");
	torture_assert_int_equal(tctx, (*r->out.job_info)->job_time, 84600000, "time");
	torture_assert_int_equal(tctx, (*r->out.job_info)->days_of_month, 0, "days of month");
	torture_assert_int_equal(tctx, (*r->out.job_info)->days_of_week, 0x2, "days of week");
	torture_assert_int_equal(tctx, (*r->out.job_info)->flags, 0x13, "flags");
	torture_assert_str_equal(tctx, (*r->out.job_info)->command, "foo.exe", "command");
	return true;
}

struct torture_suite *ndr_atsvc_suite(TALLOC_CTX *ctx)
{
	struct torture_suite *suite = torture_suite_create(ctx, "atsvc");

	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobEnum, jobenum_in_data, NDR_IN, jobenum_in_check );
	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobEnum, jobenum_out_data, NDR_OUT, jobenum_out_check );

	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobAdd, jobadd_in_data, NDR_IN, jobadd_in_check );
	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobAdd, jobadd_out_data, NDR_OUT, jobadd_out_check );

	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobDel, jobdel_in_data, NDR_IN, jobdel_in_check );
	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobDel, jobdel_out_data, NDR_OUT, jobdel_out_check );

	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobGetInfo, jobgetinfo_in_data, NDR_IN, jobgetinfo_in_check );
	torture_suite_add_ndr_pull_fn_test(suite, atsvc_JobGetInfo, jobgetinfo_out_data, NDR_OUT, jobgetinfo_out_check );

	return suite;
}
