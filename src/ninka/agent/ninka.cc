/*
 * Copyright (C) 2014-2015, Siemens AG
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include "ninka.hpp"
#include "ninkawrapper.hpp"

using namespace fo;

void scan(const fo::File& file)
{
  string ninkaResult = scanFileWithNinka(0, file);
  vector<string> ninkaLicenseNames = extractLicensesFromNinkaResult(ninkaResult);
  vector<LicenseMatch> matches = createMatches(ninkaLicenseNames);
  for (vector<LicenseMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it)
  {
    const LicenseMatch& match = *it;
    cout << (it != matches.begin() ? "," : "") << match.getLicenseName();
  }
}

int cli(int argc, char** argv)
{
  for (int i = 2; i < argc; i++)
  {
    fo::File file(i, argv[i]);
    cout << file.getFileName() << ";";
    scan(file);
    cout << ";" << endl;
  }
  return 0;
}

int main(int argc, char** argv)
{
  if (argc > 2 && strcmp("--", argv[1]) == 0)
  {
    return cli(argc, argv);
  }

  /* before parsing argv and argc make sure */
  /* to initialize the scheduler connection */

  DbManager dbManager(&argc, argv);
  NinkaDatabaseHandler databaseHandler(dbManager);

  State state = getState(dbManager);

  while (fo_scheduler_next() != NULL)
  {
    int uploadId = atoi(fo_scheduler_current());

    if (uploadId == 0) continue;

    int arsId = writeARS(state, 0, uploadId, 0, dbManager);

    if (arsId <= 0)
      bail(5);

    if (!processUploadId(state, uploadId, databaseHandler))
      bail(2);

    fo_scheduler_heart(0);
    writeARS(state, arsId, uploadId, 1, dbManager);
  }
  fo_scheduler_heart(0);

  /* do not use bail, as it would prevent the destructors from running */
  fo_scheduler_disconnect(0);
  return 0;
}
