[Previous Page](README.md)
# Contribution Guidelines

We greatly welcome and highly appreciate for your contribution. You could freely choose to either raise a GitHub issue or contributing your code change directly to our project. Please read through below guidelines before building your contribution.  

##### Table of Contents 
  * [Code of Conduct](#code-of-conduct)
  * [Licensing](#licensing)
  * [Developer Certification of Origin (DCO)](#developer-certification-of-origin-(DCO))
  * [Commit Guidelines](#commit-guidelines)
  * [Contribution Workflow](#contribution-workflow)
  * [Contributing New Components](#contributing-new-components)


## Code of Conduct

All contributors are expected to follow our [Code of Conduct](CODE_OF_CONDUCT.md). Please make sure you are welcoming and friendly in our community.

## Licensing

All SDK drivers, components, device support files, board support files and driver examples in this project are under BSD-3-Clause license, license copy please check [COPYING_BSD-3](COPYING-BSD-3). For sources using BSD-3-Clause license, you may see similar copyright as below in the head of source file.
```
/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
```
There are also components using different license, eg. the ARM CMSIS component is under [Apache License 2.0](CMSIS/LICENSE.txt). Overall license information for this project could be found in [SW-Content-Register.txt](SW-Content-Register.txt).

## Developer Certification of Origin (DCO)
Inspired by [zephyr](https://docs.zephyrproject.org/latest/contribute/index.html), we would like to adopt DCO process to encourage user contribution and avoid legally ambiguous situation. The DCO is a statement that you are the author of your contribution, and you allow our project to use your contribution under the open source license. The full statement is shown as below:
```
Developer Certificate of Origin
Version 1.1

Copyright (C) 2004, 2006 The Linux Foundation and its contributors.
660 York Street, Suite 102,
San Francisco, CA 94110 USA

Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```
If you are agree with the statement, just simply add sign-off in your commit message, following format:
```
Signed-off-by: FIRST_NAME LAST_NAME <FIRST_NAME.LAST_NAME@nxp.com>
```
### Sign-off DCO if you are using Git command line
Open Git bash to execute below commands for adding sign-off.

* Config user name and email for sign-off message

    If you are willing to configure user name and email address for every repository on you computer, use below commands:
    ```
    git config --global user.name "FIRST_NAME LAST_NAME"
    git config --global user.email "MY_NAME@example.com"
    ```
    else if you only want to set the configuration in current single repository, use:
    ```
    git config user.name "FIRST_NAME LAST_NAME"
    git config user.email "MY_NAME@example.com"
    ``` 
* Add sign-off to commit message

    This is quite simple, just use ```git commit -s ``` to commit your message, sign-off will be automatically added to your commit message. If you want to add sign-off to an existing commit, for example, the latest commit, use ```git commit --amend -s```.

### Sign-off DCO if you are using GitHub Web Editor
It's currently not supported automatically adding sign-off when you Commit change directly using GitHub Web UI. You need to manually add sign-off message in the end of your commit message. Example as below:
![Adding sing-off in GitHub UI](docs/Contributing/add_signoff_for_github_editor.png)


| :exclamation: NOTE | 
|:-----------------------------------------:| 
| DCO check will be done automatically to your pull requests. If there's sign-off mismatch issue in any commit or no sign-off is detected, the check will fails, you could check details and update your PR accordingly.|

## Commit Guidelines

### Coding Style

**Please follow the existing coding conventions in sources.** Some common rules should be followed as below:
1. Add braces to every if, else, do, while, for and switch body, even for single-line code blocks. 
2. Use 4 spaces, instead of tabs for indent.
3. Use C89-style single line comments, /*  */. The C99-style single line comment, //, is not allowed.
4. Code should be well documented, add proper doxygen comments if you are adding new function/types in existing drivers/components.

### Commit Preparation

There are some requirements for making commits, please carefully review the following guidelines before submitting your change.

Each commit message should follow below requirements:

* Have a short and clear subject line. A suggest subject line length limits to 72 characters and uses imperative mood. If it's to fix reported issue, start with ```Fixes #<issue number>```.
* Add a newline to separate subject line and description body.
* The description body should describe:
    * **What** the change does.
    * **Why** you change the approach, and
    * **How** you know it works - for example, you have verified run test on x board.
* Add sign-off in your commit.

Commits must build cleanly when applied on top of each other, thus avoiding breaking bisectability. Each commit must address a single identifiable issue and must be logically self-contained.

## Contribution Workflow
This section describes the flow for raising an issue or contributing through pull-request.

### Raise an issue

We suggest you raise an issue to report bugs only, if you are requesting new feature, please check the [Contributing New Components](#contributing-new-components) to suggest your idea.

Before submitting issue, please do below checks:
* **Rebase your code base to latest main branch to see if the issue still exists**, the issue could have already been fixed in the latest code base.
* **Check if it is stated as known-issue in release notes**, if you are not on release tag, check release notes for latest release tag on main branch.
* **Search existing GitHub issues to see if it has already been reported**, the same issue could be raised by other developers already.

If above checks does not help the issue, you may report issue via [New issue](https://github.com/NXPmicro/mcux-sdk/issues/new/choose), please follow the template to describe your issue, explain the problem and include additional details to help us reproduce and move on efficiently.

### Create a pull-request

If you want to contribute your code back to our project, need to follow the pull-request flow. Knowledge for **Git** is required with below steps.

| :exclamation: NOTE | 
|:-----------------------------------------:| 
| If you want to contribute new features, please make sure the new features are communicated follow the flow [Contributing New Components](#contributing-new-components) firstly.|

1. Click ‘Fork’ on our GitHub project, create a forked repo to your personal GitHub account. eg. ```yourname/mcux-sdk```
2. Clone your forked repo to local repository. ```git clone https://github.com/yourname/mcux-sdk.git```
3. Change into the ```mcux-sdk``` folder which hosts local repository.
    ```
    cd mcux-sdk
    ```
4. Add new remote ```nxp``` in the repository to be able to get latest code base in ```NXPMicro/mcux-sdk```.
    ```
    git remote add nxp https://github.com/NXPmicro/mcux-sdk.git
    ```
5. Checkout a new branch for your contribution, the branch should be check out from the origin branch you want to contribute back to. eg. nxp/main branch
    ```
    git fetch nxp
    git checkout -b bugfix/fixing_yy nxp/main
    ```
6. Do code your change, commit the change in local branch. The coding style and commit preparation should follow [Commit Guidelines](#commit-guidelines):
    ```
    git add xxx
    git commit -s 
    ```
7. Push your local branch to your remote github repo.
    ```
    git push origin HEAD:bugfix/fixing_yy
    ```
8. Go to your forked repo on GitHub and click on the Compare & pull request button for the branch you just pushed to open a pull request. Please also follow the template description to describe your pull request to help reviewers to understand your logic. 

    For the final step to update pull-request to incorporate all suggested changes in review comments, **although it's not suggested but it's OK** to amend your previous commit and use force push to update your PR conveniently.


## Contributing New Components
If you want to contribute new components, please send an email to [project maintainer](susan.su@nxp.com) to communicate your idea first. If the new component has a different license other than BSD-3-Clause, you need to prepare a description for the license information in the email description for us to decide whether the contribution will pollute the project. Description for the new license need to follow the component entry in [SW-Content-Register.txt](SW-Content-Register.txt).

